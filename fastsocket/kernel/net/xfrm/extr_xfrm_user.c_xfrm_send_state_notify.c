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
struct xfrm_state {int dummy; } ;
struct km_event {int event; } ;

/* Variables and functions */
#define  XFRM_MSG_DELSA 133 
#define  XFRM_MSG_EXPIRE 132 
#define  XFRM_MSG_FLUSHSA 131 
#define  XFRM_MSG_NEWAE 130 
#define  XFRM_MSG_NEWSA 129 
#define  XFRM_MSG_UPDSA 128 
 int /*<<< orphan*/  printk (char*,int) ; 
 int xfrm_aevent_state_notify (struct xfrm_state*,struct km_event*) ; 
 int xfrm_exp_state_notify (struct xfrm_state*,struct km_event*) ; 
 int xfrm_notify_sa (struct xfrm_state*,struct km_event*) ; 
 int xfrm_notify_sa_flush (struct km_event*) ; 

__attribute__((used)) static int xfrm_send_state_notify(struct xfrm_state *x, struct km_event *c)
{

	switch (c->event) {
	case XFRM_MSG_EXPIRE:
		return xfrm_exp_state_notify(x, c);
	case XFRM_MSG_NEWAE:
		return xfrm_aevent_state_notify(x, c);
	case XFRM_MSG_DELSA:
	case XFRM_MSG_UPDSA:
	case XFRM_MSG_NEWSA:
		return xfrm_notify_sa(x, c);
	case XFRM_MSG_FLUSHSA:
		return xfrm_notify_sa_flush(c);
	default:
		 printk("xfrm_user: Unknown SA event %d\n", c->event);
		 break;
	}

	return 0;

}