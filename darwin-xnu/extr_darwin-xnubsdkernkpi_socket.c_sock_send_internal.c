#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * uio_t ;
typedef  int /*<<< orphan*/  uio_buf ;
struct sockaddr {int dummy; } ;
struct msghdr {int msg_iovlen; scalar_t__ msg_name; scalar_t__ msg_controllen; scalar_t__ msg_control; struct iovec* msg_iov; } ;
struct TYPE_7__ {int len; } ;
struct mbuf {scalar_t__ m_len; TYPE_1__ m_pkthdr; } ;
struct iovec {int /*<<< orphan*/  iov_len; int /*<<< orphan*/  iov_base; } ;
struct cmsghdr {int dummy; } ;
typedef  TYPE_4__* socket_t ;
typedef  struct mbuf* mbuf_t ;
typedef  int errno_t ;
struct TYPE_10__ {TYPE_3__* so_proto; } ;
struct TYPE_9__ {TYPE_2__* pr_usrreqs; } ;
struct TYPE_8__ {int (* pru_sosend ) (TYPE_4__*,struct sockaddr*,int /*<<< orphan*/ *,struct mbuf*,struct mbuf*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CAST_USER_ADDR_T (int /*<<< orphan*/ ) ; 
 int EINTR ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ERESTART ; 
 int EWOULDBLOCK ; 
 size_t MLEN ; 
 int /*<<< orphan*/  MT_CONTROL ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int UIO_SIZEOF (int) ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  UIO_WRITE ; 
 int /*<<< orphan*/  caddr_t ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* m_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mtod (struct mbuf*,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_4__*,struct sockaddr*,int /*<<< orphan*/ *,struct mbuf*,struct mbuf*,int) ; 
 int /*<<< orphan*/  uio_addiov (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * uio_createwithbuffer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int uio_resid (int /*<<< orphan*/ *) ; 

errno_t
sock_send_internal(socket_t sock, const struct msghdr *msg, mbuf_t data,
    int flags, size_t *sentlen)
{
	uio_t auio = NULL;
	struct mbuf *control = NULL;
	int error = 0;
	int datalen = 0;
	char uio_buf[ UIO_SIZEOF((msg != NULL ? msg->msg_iovlen : 1)) ];

	if (sock == NULL) {
		error = EINVAL;
		goto errorout;
	}

	if (data == NULL && msg != NULL) {
		struct iovec *tempp = msg->msg_iov;

		auio = uio_createwithbuffer(msg->msg_iovlen, 0,
		    UIO_SYSSPACE, UIO_WRITE, &uio_buf[0], sizeof (uio_buf));
		if (tempp != NULL) {
			int i;

			for (i = 0; i < msg->msg_iovlen; i++) {
				uio_addiov(auio,
				    CAST_USER_ADDR_T((tempp + i)->iov_base),
				    (tempp + i)->iov_len);
			}

			if (uio_resid(auio) < 0) {
				error = EINVAL;
				goto errorout;
			}
		}
	}

	if (sentlen != NULL)
		*sentlen = 0;

	if (auio != NULL)
		datalen = uio_resid(auio);
	else
		datalen = data->m_pkthdr.len;

	if (msg != NULL && msg->msg_control) {
		if ((size_t)msg->msg_controllen < sizeof (struct cmsghdr)) {
			error = EINVAL;
			goto errorout;
		}

		if ((size_t)msg->msg_controllen > MLEN) {
			error = EINVAL;
			goto errorout;
		}

		control = m_get(M_NOWAIT, MT_CONTROL);
		if (control == NULL) {
			error = ENOMEM;
			goto errorout;
		}
		memcpy(mtod(control, caddr_t), msg->msg_control,
		    msg->msg_controllen);
		control->m_len = msg->msg_controllen;
	}

	error = sock->so_proto->pr_usrreqs->pru_sosend(sock, msg != NULL ?
	    (struct sockaddr *)msg->msg_name : NULL, auio, data,
	    control, flags);

	/*
	 * Residual data is possible in the case of IO vectors but not
	 * in the mbuf case since the latter is treated as atomic send.
	 * If pru_sosend() consumed a portion of the iovecs data and
	 * the error returned is transient, treat it as success; this
	 * is consistent with sendit() behavior.
	 */
	if (auio != NULL && uio_resid(auio) != datalen &&
	    (error == ERESTART || error == EINTR || error == EWOULDBLOCK))
		error = 0;

	if (error == 0 && sentlen != NULL) {
		if (auio != NULL)
			*sentlen = datalen - uio_resid(auio);
		else
			*sentlen = datalen;
	}

	return (error);

/*
 * In cases where we detect an error before returning, we need to
 * free the mbuf chain if there is one. sosend (and pru_sosend) will
 * free the mbuf chain if they encounter an error.
 */
errorout:
	if (control)
		m_freem(control);
	if (data)
		m_freem(data);
	if (sentlen)
		*sentlen = 0;
	return (error);
}