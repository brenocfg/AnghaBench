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
#define  ERR_IE_COMPREHENSION 131 
#define  ERR_IE_LENGTH 130 
#define  ERR_IE_SEQUENCE 129 
#define  ERR_IE_UNRECOGNIZED 128 
 int L3_DEB_CHECK ; 
 int /*<<< orphan*/  l3_debug (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  l3ni1_status_send (struct l3_process*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
l3ni1_std_ie_err(struct l3_process *pc, int ret) {

	if (pc->debug & L3_DEB_CHECK)
		l3_debug(pc->st, "check_infoelements ret %d", ret);
	switch(ret) {
		case 0: 
			break;
		case ERR_IE_COMPREHENSION:
			pc->para.cause = 96;
			l3ni1_status_send(pc, 0, NULL);
			break;
		case ERR_IE_UNRECOGNIZED:
			pc->para.cause = 99;
			l3ni1_status_send(pc, 0, NULL);
			break;
		case ERR_IE_LENGTH:
			pc->para.cause = 100;
			l3ni1_status_send(pc, 0, NULL);
			break;
		case ERR_IE_SEQUENCE:
		default:
			break;
	}
}