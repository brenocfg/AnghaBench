#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sctp_sndrcvinfo {int dummy; } ;
struct msghdr {char* msg_control; int msg_controllen; int msg_flags; } ;
struct kvec {unsigned int iov_len; scalar_t__ iov_base; } ;
struct TYPE_6__ {scalar_t__ base; int /*<<< orphan*/  len; } ;
struct connection {scalar_t__ nodeid; int /*<<< orphan*/  sock_mutex; int /*<<< orphan*/  rwork; int /*<<< orphan*/  flags; int /*<<< orphan*/ * rx_page; TYPE_1__ cb; int /*<<< orphan*/ * sock; } ;
typedef  int /*<<< orphan*/  incmsg ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CF_READ_PENDING ; 
 int CMSG_SPACE (int) ; 
 int EAGAIN ; 
 int EBADMSG ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int MSG_DONTWAIT ; 
 int MSG_NOSIGNAL ; 
 int MSG_NOTIFICATION ; 
 scalar_t__ PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cbuf_add (TYPE_1__*,int) ; 
 scalar_t__ cbuf_data (TYPE_1__*) ; 
 int /*<<< orphan*/  cbuf_eat (TYPE_1__*,int) ; 
 scalar_t__ cbuf_empty (TYPE_1__*) ; 
 int /*<<< orphan*/  cbuf_init (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  close_connection (struct connection*,int) ; 
 int dlm_process_incoming_buffer (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int kernel_recvmsg (int /*<<< orphan*/ *,struct msghdr*,struct kvec*,int,unsigned int,int) ; 
 int /*<<< orphan*/  log_print (char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,unsigned int,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (char**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ page_address (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_sctp_notification (struct connection*,struct msghdr*,scalar_t__) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  recv_workqueue ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int receive_from_sock(struct connection *con)
{
	int ret = 0;
	struct msghdr msg = {};
	struct kvec iov[2];
	unsigned len;
	int r;
	int call_again_soon = 0;
	int nvec;
	char incmsg[CMSG_SPACE(sizeof(struct sctp_sndrcvinfo))];

	mutex_lock(&con->sock_mutex);

	if (con->sock == NULL) {
		ret = -EAGAIN;
		goto out_close;
	}

	if (con->rx_page == NULL) {
		/*
		 * This doesn't need to be atomic, but I think it should
		 * improve performance if it is.
		 */
		con->rx_page = alloc_page(GFP_ATOMIC);
		if (con->rx_page == NULL)
			goto out_resched;
		cbuf_init(&con->cb, PAGE_CACHE_SIZE);
	}

	/* Only SCTP needs these really */
	memset(&incmsg, 0, sizeof(incmsg));
	msg.msg_control = incmsg;
	msg.msg_controllen = sizeof(incmsg);

	/*
	 * iov[0] is the bit of the circular buffer between the current end
	 * point (cb.base + cb.len) and the end of the buffer.
	 */
	iov[0].iov_len = con->cb.base - cbuf_data(&con->cb);
	iov[0].iov_base = page_address(con->rx_page) + cbuf_data(&con->cb);
	iov[1].iov_len = 0;
	nvec = 1;

	/*
	 * iov[1] is the bit of the circular buffer between the start of the
	 * buffer and the start of the currently used section (cb.base)
	 */
	if (cbuf_data(&con->cb) >= con->cb.base) {
		iov[0].iov_len = PAGE_CACHE_SIZE - cbuf_data(&con->cb);
		iov[1].iov_len = con->cb.base;
		iov[1].iov_base = page_address(con->rx_page);
		nvec = 2;
	}
	len = iov[0].iov_len + iov[1].iov_len;

	r = ret = kernel_recvmsg(con->sock, &msg, iov, nvec, len,
			       MSG_DONTWAIT | MSG_NOSIGNAL);
	if (ret <= 0)
		goto out_close;

	/* Process SCTP notifications */
	if (msg.msg_flags & MSG_NOTIFICATION) {
		msg.msg_control = incmsg;
		msg.msg_controllen = sizeof(incmsg);

		process_sctp_notification(con, &msg,
				page_address(con->rx_page) + con->cb.base);
		mutex_unlock(&con->sock_mutex);
		return 0;
	}
	BUG_ON(con->nodeid == 0);

	if (ret == len)
		call_again_soon = 1;
	cbuf_add(&con->cb, ret);
	ret = dlm_process_incoming_buffer(con->nodeid,
					  page_address(con->rx_page),
					  con->cb.base, con->cb.len,
					  PAGE_CACHE_SIZE);
	if (ret == -EBADMSG) {
		log_print("lowcomms: addr=%p, base=%u, len=%u, "
			  "iov_len=%u, iov_base[0]=%p, read=%d",
			  page_address(con->rx_page), con->cb.base, con->cb.len,
			  len, iov[0].iov_base, r);
	}
	if (ret < 0)
		goto out_close;
	cbuf_eat(&con->cb, ret);

	if (cbuf_empty(&con->cb) && !call_again_soon) {
		__free_page(con->rx_page);
		con->rx_page = NULL;
	}

	if (call_again_soon)
		goto out_resched;
	mutex_unlock(&con->sock_mutex);
	return 0;

out_resched:
	if (!test_and_set_bit(CF_READ_PENDING, &con->flags))
		queue_work(recv_workqueue, &con->rwork);
	mutex_unlock(&con->sock_mutex);
	return -EAGAIN;

out_close:
	mutex_unlock(&con->sock_mutex);
	if (ret != -EAGAIN) {
		close_connection(con, false);
		/* Reconnect when there is something to send */
	}
	/* Don't return success if we really got EOF */
	if (ret == 0)
		ret = -EAGAIN;

	return ret;
}