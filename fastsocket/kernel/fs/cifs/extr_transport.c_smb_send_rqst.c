#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  val ;
struct socket {int dummy; } ;
struct smb_rqst {int rq_nvec; unsigned int rq_npages; int /*<<< orphan*/ * rq_pages; struct kvec* rq_iov; } ;
struct kvec {int /*<<< orphan*/  iov_len; int /*<<< orphan*/  iov_base; } ;
struct TCP_Server_Info {int /*<<< orphan*/  tcpStatus; struct socket* ssocket; } ;

/* Variables and functions */
 int /*<<< orphan*/  CifsNeedReconnect ; 
 int EINTR ; 
 int EIO ; 
 int ENOTSOCK ; 
 int /*<<< orphan*/  SOL_TCP ; 
 int /*<<< orphan*/  TCP_CORK ; 
 int /*<<< orphan*/  WARN (int,char*,unsigned long,unsigned int) ; 
 int /*<<< orphan*/  cERROR (int,char*,int) ; 
 int /*<<< orphan*/  cFYI (int,char*,unsigned int,...) ; 
 int /*<<< orphan*/  cifs_rqst_page_to_kvec (struct smb_rqst*,unsigned int,struct kvec*) ; 
 int /*<<< orphan*/  dump_smb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int get_rfc1002_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_setsockopt (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kunmap (int /*<<< orphan*/ ) ; 
 unsigned long rqst_len (struct smb_rqst*) ; 
 int smb_send_kvec (struct TCP_Server_Info*,struct kvec*,int,size_t*) ; 

__attribute__((used)) static int
smb_send_rqst(struct TCP_Server_Info *server, struct smb_rqst *rqst)
{
	int rc;
	struct kvec *iov = rqst->rq_iov;
	int n_vec = rqst->rq_nvec;
	unsigned int smb_buf_length = get_rfc1002_length(iov[0].iov_base);
	unsigned long send_length;
	unsigned int i;
	size_t total_len = 0, sent;
	struct socket *ssocket = server->ssocket;
	int val = 1;

	if (ssocket == NULL)
		return -ENOTSOCK;

	/* sanity check send length */
	send_length = rqst_len(rqst);
	if (send_length != smb_buf_length + 4) {
		WARN(1, "Send length mismatch(send_length=%lu smb_buf_length=%u)\n", send_length, smb_buf_length);
		return -EIO;
	}

	cFYI(1, "Sending smb: smb_len=%u", smb_buf_length);
	dump_smb(iov[0].iov_base, iov[0].iov_len);

	/* cork the socket */
	kernel_setsockopt(ssocket, SOL_TCP, TCP_CORK,
				(char *)&val, sizeof(val));

	rc = smb_send_kvec(server, iov, n_vec, &sent);
	if (rc < 0)
		goto uncork;

	total_len += sent;

	/* now walk the page array and send each page in it */
	for (i = 0; i < rqst->rq_npages; i++) {
		struct kvec p_iov;

		cifs_rqst_page_to_kvec(rqst, i, &p_iov);
		rc = smb_send_kvec(server, &p_iov, 1, &sent);
		kunmap(rqst->rq_pages[i]);
		if (rc < 0)
			break;

		total_len += sent;
	}

uncork:
	/* uncork it */
	val = 0;
	kernel_setsockopt(ssocket, SOL_TCP, TCP_CORK,
				(char *)&val, sizeof(val));

	if ((total_len > 0) && (total_len != smb_buf_length + 4)) {
		cFYI(1, "partial send (wanted=%u sent=%zu): terminating "
			"session", smb_buf_length + 4, total_len);
		/*
		 * If we have only sent part of an SMB then the next SMB could
		 * be taken as the remainder of this one. We need to kill the
		 * socket so the server throws away the partial SMB
		 */
		server->tcpStatus = CifsNeedReconnect;
	}

	if (rc < 0 && rc != -EINTR)
		cERROR(1, "Error %d sending data on socket to server", rc);
	else
		rc = 0;

	return rc;
}