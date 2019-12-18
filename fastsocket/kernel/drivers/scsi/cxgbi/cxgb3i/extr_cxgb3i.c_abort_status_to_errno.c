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
struct cxgbi_sock {int /*<<< orphan*/  state; } ;

/* Variables and functions */
#define  CPL_ERR_BAD_SYN 133 
#define  CPL_ERR_CONN_RESET 132 
#define  CPL_ERR_FINWAIT2_TIMEDOUT 131 
#define  CPL_ERR_KEEPALIVE_TIMEDOUT 130 
#define  CPL_ERR_PERSIST_TIMEDOUT 129 
#define  CPL_ERR_XMIT_TIMEDOUT 128 
 int /*<<< orphan*/  CTP_ESTABLISHED ; 
 int ECONNRESET ; 
 int EIO ; 
 int EPIPE ; 
 int ETIMEDOUT ; 

__attribute__((used)) static int abort_status_to_errno(struct cxgbi_sock *csk, int abort_reason,
				 int *need_rst)
{
	switch (abort_reason) {
	case CPL_ERR_BAD_SYN: /* fall through */
	case CPL_ERR_CONN_RESET:
		return csk->state > CTP_ESTABLISHED ? -EPIPE : -ECONNRESET;
	case CPL_ERR_XMIT_TIMEDOUT:
	case CPL_ERR_PERSIST_TIMEDOUT:
	case CPL_ERR_FINWAIT2_TIMEDOUT:
	case CPL_ERR_KEEPALIVE_TIMEDOUT:
		return -ETIMEDOUT;
	default:
		return -EIO;
	}
}