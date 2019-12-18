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
struct HvLpEvent {int flags; int xSubtype; int xSizeMinus1; int /*<<< orphan*/  xTargetInstanceId; int /*<<< orphan*/  xSourceInstanceId; int /*<<< orphan*/  xTargetLp; int /*<<< orphan*/  xSourceLp; int /*<<< orphan*/  xType; } ;
struct viocharlpevent {struct HvLpEvent event; } ;
typedef  int /*<<< orphan*/  HvLpIndex ;

/* Variables and functions */
 int HV_LP_EVENT_DEFERRED_ACK ; 
 int HV_LP_EVENT_INT ; 
 int HV_LP_EVENT_VALID ; 
 int /*<<< orphan*/  HvLpConfig_getLpIndex () ; 
 int /*<<< orphan*/  HvLpEvent_Type_VirtualIo ; 
 int /*<<< orphan*/  memset (struct viocharlpevent*,int /*<<< orphan*/ ,int) ; 
 int viochardata ; 
 int viomajorsubtype_chario ; 
 int /*<<< orphan*/  viopath_sourceinst (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  viopath_targetinst (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_data_event(struct viocharlpevent *viochar, HvLpIndex lp)
{
	struct HvLpEvent *hev = &viochar->event;

	memset(viochar, 0, sizeof(struct viocharlpevent));

	hev->flags = HV_LP_EVENT_VALID | HV_LP_EVENT_DEFERRED_ACK |
		HV_LP_EVENT_INT;
	hev->xType = HvLpEvent_Type_VirtualIo;
	hev->xSubtype = viomajorsubtype_chario | viochardata;
	hev->xSourceLp = HvLpConfig_getLpIndex();
	hev->xTargetLp = lp;
	hev->xSizeMinus1 = sizeof(struct viocharlpevent);
	hev->xSourceInstanceId = viopath_sourceinst(lp);
	hev->xTargetInstanceId = viopath_targetinst(lp);
}