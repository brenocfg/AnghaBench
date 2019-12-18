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
struct socket {int dummy; } ;
struct msghdr {size_t msg_iovlen; struct iovec* msg_iov; } ;
struct kvec {int dummy; } ;
struct iovec {int dummy; } ;
typedef  int /*<<< orphan*/  mm_segment_t ;

/* Variables and functions */
 int EINVAL ; 
 int EPIPE ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  get_ds () ; 
 int /*<<< orphan*/  get_fs () ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  set_fs (int /*<<< orphan*/ ) ; 
 int sock_sendmsg (struct socket*,struct msghdr*,size_t) ; 

__attribute__((used)) static int o2net_send_tcp_msg(struct socket *sock, struct kvec *vec,
			      size_t veclen, size_t total)
{
	int ret;
	mm_segment_t oldfs;
	struct msghdr msg = {
		.msg_iov = (struct iovec *)vec,
		.msg_iovlen = veclen,
	};

	if (sock == NULL) {
		ret = -EINVAL;
		goto out;
	}

	oldfs = get_fs();
	set_fs(get_ds());
	ret = sock_sendmsg(sock, &msg, total);
	set_fs(oldfs);
	if (ret != total) {
		mlog(ML_ERROR, "sendmsg returned %d instead of %zu\n", ret,
		     total);
		if (ret >= 0)
			ret = -EPIPE; /* should be smarter, I bet */
		goto out;
	}

	ret = 0;
out:
	if (ret < 0)
		mlog(0, "returning error: %d\n", ret);
	return ret;
}