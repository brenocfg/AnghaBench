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
struct sock {int dummy; } ;
struct pppol2tp_session {int recv_seq; int debug; int send_seq; int lns_mode; int /*<<< orphan*/  name; int /*<<< orphan*/  reorder_timeout; } ;

/* Variables and functions */
 int ENOPROTOOPT ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  PPPOL2TP_MSG_CONTROL ; 
#define  PPPOL2TP_SO_DEBUG 132 
#define  PPPOL2TP_SO_LNSMODE 131 
#define  PPPOL2TP_SO_RECVSEQ 130 
#define  PPPOL2TP_SO_REORDERTO 129 
#define  PPPOL2TP_SO_SENDSEQ 128 
 int /*<<< orphan*/  PRINTK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ jiffies_to_msecs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pppol2tp_session_getsockopt(struct sock *sk,
				       struct pppol2tp_session *session,
				       int optname, int *val)
{
	int err = 0;

	switch (optname) {
	case PPPOL2TP_SO_RECVSEQ:
		*val = session->recv_seq;
		PRINTK(session->debug, PPPOL2TP_MSG_CONTROL, KERN_INFO,
		       "%s: get recv_seq=%d\n", session->name, *val);
		break;

	case PPPOL2TP_SO_SENDSEQ:
		*val = session->send_seq;
		PRINTK(session->debug, PPPOL2TP_MSG_CONTROL, KERN_INFO,
		       "%s: get send_seq=%d\n", session->name, *val);
		break;

	case PPPOL2TP_SO_LNSMODE:
		*val = session->lns_mode;
		PRINTK(session->debug, PPPOL2TP_MSG_CONTROL, KERN_INFO,
		       "%s: get lns_mode=%d\n", session->name, *val);
		break;

	case PPPOL2TP_SO_DEBUG:
		*val = session->debug;
		PRINTK(session->debug, PPPOL2TP_MSG_CONTROL, KERN_INFO,
		       "%s: get debug=%d\n", session->name, *val);
		break;

	case PPPOL2TP_SO_REORDERTO:
		*val = (int) jiffies_to_msecs(session->reorder_timeout);
		PRINTK(session->debug, PPPOL2TP_MSG_CONTROL, KERN_INFO,
		       "%s: get reorder_timeout=%d\n", session->name, *val);
		break;

	default:
		err = -ENOPROTOOPT;
	}

	return err;
}