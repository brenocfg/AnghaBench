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
struct TYPE_2__ {int cause; } ;
struct l3_process {int debug; TYPE_1__ para; int /*<<< orphan*/  st; } ;

/* Variables and functions */
 int L3_DEB_CHECK ; 
 int L3_DEB_WARN ; 
#define  MT_ALERTING 152 
#define  MT_CALL_PROCEEDING 151 
#define  MT_CONGESTION_CONTROL 150 
#define  MT_CONNECT 149 
#define  MT_CONNECT_ACKNOWLEDGE 148 
#define  MT_DISCONNECT 147 
#define  MT_FACILITY 146 
#define  MT_INFORMATION 145 
#define  MT_NOTIFY 144 
#define  MT_PROGRESS 143 
#define  MT_RELEASE 142 
#define  MT_RELEASE_COMPLETE 141 
#define  MT_RESTART 140 
#define  MT_RESTART_ACKNOWLEDGE 139 
#define  MT_RESUME 138 
#define  MT_RESUME_ACKNOWLEDGE 137 
#define  MT_RESUME_REJECT 136 
#define  MT_SETUP 135 
#define  MT_SETUP_ACKNOWLEDGE 134 
#define  MT_STATUS 133 
#define  MT_STATUS_ENQUIRY 132 
#define  MT_SUSPEND 131 
#define  MT_SUSPEND_ACKNOWLEDGE 130 
#define  MT_SUSPEND_REJECT 129 
#define  MT_USER_INFORMATION 128 
 int /*<<< orphan*/  l3_debug (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  l3ni1_status_send (struct l3_process*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
l3ni1_check_messagetype_validity(struct l3_process *pc, int mt, void *arg)
{
	switch (mt) {
		case MT_ALERTING:
		case MT_CALL_PROCEEDING:
		case MT_CONNECT:
		case MT_CONNECT_ACKNOWLEDGE:
		case MT_DISCONNECT:
		case MT_INFORMATION:
		case MT_FACILITY:
		case MT_NOTIFY:
		case MT_PROGRESS:
		case MT_RELEASE:
		case MT_RELEASE_COMPLETE:
		case MT_SETUP:
		case MT_SETUP_ACKNOWLEDGE:
		case MT_RESUME_ACKNOWLEDGE:
		case MT_RESUME_REJECT:
		case MT_SUSPEND_ACKNOWLEDGE:
		case MT_SUSPEND_REJECT:
		case MT_USER_INFORMATION:
		case MT_RESTART:
		case MT_RESTART_ACKNOWLEDGE:
		case MT_CONGESTION_CONTROL:
		case MT_STATUS:
		case MT_STATUS_ENQUIRY:
			if (pc->debug & L3_DEB_CHECK)
				l3_debug(pc->st, "l3ni1_check_messagetype_validity mt(%x) OK", mt);
			break;
		case MT_RESUME: /* RESUME only in user->net */
		case MT_SUSPEND: /* SUSPEND only in user->net */
		default:
			if (pc->debug & (L3_DEB_CHECK | L3_DEB_WARN))
				l3_debug(pc->st, "l3ni1_check_messagetype_validity mt(%x) fail", mt);
			pc->para.cause = 97;
			l3ni1_status_send(pc, 0, NULL);
			return(1);
	}
	return(0);
}