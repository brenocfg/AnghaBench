#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hdrlen; } ;
struct pppox_sock {TYPE_1__ chan; } ;
struct pppol2tp_session {int recv_seq; int debug; int send_seq; int lns_mode; int reorder_timeout; int /*<<< orphan*/  name; struct sock* sock; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOPROTOOPT ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  PPPOL2TP_L2TP_HDR_SIZE_NOSEQ ; 
 int /*<<< orphan*/  PPPOL2TP_L2TP_HDR_SIZE_SEQ ; 
 int /*<<< orphan*/  PPPOL2TP_MSG_CONTROL ; 
#define  PPPOL2TP_SO_DEBUG 132 
#define  PPPOL2TP_SO_LNSMODE 131 
#define  PPPOL2TP_SO_RECVSEQ 130 
#define  PPPOL2TP_SO_REORDERTO 129 
#define  PPPOL2TP_SO_SENDSEQ 128 
 int /*<<< orphan*/  PRINTK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int msecs_to_jiffies (int) ; 
 struct pppox_sock* pppox_sk (struct sock*) ; 

__attribute__((used)) static int pppol2tp_session_setsockopt(struct sock *sk,
				       struct pppol2tp_session *session,
				       int optname, int val)
{
	int err = 0;

	switch (optname) {
	case PPPOL2TP_SO_RECVSEQ:
		if ((val != 0) && (val != 1)) {
			err = -EINVAL;
			break;
		}
		session->recv_seq = val ? -1 : 0;
		PRINTK(session->debug, PPPOL2TP_MSG_CONTROL, KERN_INFO,
		       "%s: set recv_seq=%d\n", session->name,
		       session->recv_seq);
		break;

	case PPPOL2TP_SO_SENDSEQ:
		if ((val != 0) && (val != 1)) {
			err = -EINVAL;
			break;
		}
		session->send_seq = val ? -1 : 0;
		{
			struct sock *ssk      = session->sock;
			struct pppox_sock *po = pppox_sk(ssk);
			po->chan.hdrlen = val ? PPPOL2TP_L2TP_HDR_SIZE_SEQ :
				PPPOL2TP_L2TP_HDR_SIZE_NOSEQ;
		}
		PRINTK(session->debug, PPPOL2TP_MSG_CONTROL, KERN_INFO,
		       "%s: set send_seq=%d\n", session->name, session->send_seq);
		break;

	case PPPOL2TP_SO_LNSMODE:
		if ((val != 0) && (val != 1)) {
			err = -EINVAL;
			break;
		}
		session->lns_mode = val ? -1 : 0;
		PRINTK(session->debug, PPPOL2TP_MSG_CONTROL, KERN_INFO,
		       "%s: set lns_mode=%d\n", session->name,
		       session->lns_mode);
		break;

	case PPPOL2TP_SO_DEBUG:
		session->debug = val;
		PRINTK(session->debug, PPPOL2TP_MSG_CONTROL, KERN_INFO,
		       "%s: set debug=%x\n", session->name, session->debug);
		break;

	case PPPOL2TP_SO_REORDERTO:
		session->reorder_timeout = msecs_to_jiffies(val);
		PRINTK(session->debug, PPPOL2TP_MSG_CONTROL, KERN_INFO,
		       "%s: set reorder_timeout=%d\n", session->name,
		       session->reorder_timeout);
		break;

	default:
		err = -ENOPROTOOPT;
		break;
	}

	return err;
}