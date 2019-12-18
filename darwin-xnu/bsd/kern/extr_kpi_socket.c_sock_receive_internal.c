#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uio_t ;
typedef  int /*<<< orphan*/  uio_buf ;
typedef  int /*<<< orphan*/  u_char ;
struct sockaddr {unsigned int sa_len; } ;
struct msghdr {int msg_iovlen; int msg_flags; int msg_namelen; int msg_controllen; int /*<<< orphan*/ * msg_control; int /*<<< orphan*/ * msg_name; struct iovec* msg_iov; } ;
struct mbuf {int m_len; struct mbuf* m_next; } ;
struct iovec {int /*<<< orphan*/  iov_len; int /*<<< orphan*/  iov_base; } ;
typedef  TYPE_3__* socket_t ;
typedef  int /*<<< orphan*/  mbuf_t ;
typedef  int errno_t ;
struct TYPE_8__ {TYPE_2__* so_proto; } ;
struct TYPE_7__ {TYPE_1__* pr_usrreqs; } ;
struct TYPE_6__ {int (* pru_soreceive ) (TYPE_3__*,struct sockaddr**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mbuf**,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CAST_USER_ADDR_T (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  FREE (struct sockaddr*,int /*<<< orphan*/ ) ; 
 int MIN (int,unsigned int) ; 
 int MSG_CTRUNC ; 
 int /*<<< orphan*/  M_SONAME ; 
 int /*<<< orphan*/  UIO_READ ; 
 int UIO_SIZEOF (int) ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  caddr_t ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr*,unsigned int) ; 
 struct sockaddr* mtod (struct mbuf*,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_3__*,struct sockaddr**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mbuf**,int*) ; 
 int /*<<< orphan*/  uio_addiov (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uio_createwithbuffer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int uio_resid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uio_setresid (int /*<<< orphan*/ ,size_t) ; 

errno_t
sock_receive_internal(socket_t sock, struct msghdr *msg, mbuf_t *data,
    int flags, size_t *recvdlen)
{
	uio_t auio;
	struct mbuf *control = NULL;
	int error = 0;
	int length = 0;
	struct sockaddr	*fromsa = NULL;
	char uio_buf[ UIO_SIZEOF((msg != NULL) ? msg->msg_iovlen : 0) ];

	if (sock == NULL)
		return (EINVAL);

	auio = uio_createwithbuffer(((msg != NULL) ? msg->msg_iovlen : 0),
	    0, UIO_SYSSPACE, UIO_READ, &uio_buf[0], sizeof (uio_buf));
	if (msg != NULL && data == NULL) {
		int i;
		struct iovec *tempp = msg->msg_iov;

		for (i = 0; i < msg->msg_iovlen; i++) {
			uio_addiov(auio,
			    CAST_USER_ADDR_T((tempp + i)->iov_base),
			    (tempp + i)->iov_len);
		}
		if (uio_resid(auio) < 0)
			return (EINVAL);
	} else if (recvdlen != NULL) {
		uio_setresid(auio, (uio_resid(auio) + *recvdlen));
	}
	length = uio_resid(auio);

	if (recvdlen != NULL)
		*recvdlen = 0;

	/* let pru_soreceive handle the socket locking */
	error = sock->so_proto->pr_usrreqs->pru_soreceive(sock, &fromsa, auio,
	    data, (msg && msg->msg_control) ? &control : NULL, &flags);
	if (error != 0)
		goto cleanup;

	if (recvdlen != NULL)
		*recvdlen = length - uio_resid(auio);
	if (msg != NULL) {
		msg->msg_flags = flags;

		if (msg->msg_name != NULL) {
			int salen;
			salen = msg->msg_namelen;
			if (msg->msg_namelen > 0 && fromsa != NULL) {
				salen = MIN(salen, fromsa->sa_len);
				memcpy(msg->msg_name, fromsa,
				    msg->msg_namelen > fromsa->sa_len ?
				    fromsa->sa_len : msg->msg_namelen);
			}
		}

		if (msg->msg_control != NULL) {
			struct mbuf *m = control;
			u_char *ctlbuf = msg->msg_control;
			int clen = msg->msg_controllen;

			msg->msg_controllen = 0;

			while (m != NULL && clen > 0) {
				unsigned int tocopy;

				if (clen >= m->m_len) {
					tocopy = m->m_len;
				} else {
					msg->msg_flags |= MSG_CTRUNC;
					tocopy = clen;
				}
				memcpy(ctlbuf, mtod(m, caddr_t), tocopy);
				ctlbuf += tocopy;
				clen -= tocopy;
				m = m->m_next;
			}
			msg->msg_controllen =
			    (uintptr_t)ctlbuf - (uintptr_t)msg->msg_control;
		}
	}

cleanup:
	if (control != NULL)
		m_freem(control);
	if (fromsa != NULL)
		FREE(fromsa, M_SONAME);
	return (error);
}