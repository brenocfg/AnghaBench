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
typedef  int u32 ;
struct afs_call {int /*<<< orphan*/ * type; int /*<<< orphan*/  operation_ID; } ;

/* Variables and functions */
#define  CBCallBack 132 
#define  CBInitCallBackState 131 
#define  CBInitCallBackState3 130 
#define  CBProbe 129 
#define  CBTellMeAboutYourself 128 
 int /*<<< orphan*/  _enter (char*,int) ; 
 int /*<<< orphan*/  afs_SRXCBCallBack ; 
 int /*<<< orphan*/  afs_SRXCBInitCallBackState ; 
 int /*<<< orphan*/  afs_SRXCBInitCallBackState3 ; 
 int /*<<< orphan*/  afs_SRXCBProbe ; 
 int /*<<< orphan*/  afs_SRXCBTellMeAboutYourself ; 
 int ntohl (int /*<<< orphan*/ ) ; 

bool afs_cm_incoming_call(struct afs_call *call)
{
	u32 operation_id = ntohl(call->operation_ID);

	_enter("{CB.OP %u}", operation_id);

	switch (operation_id) {
	case CBCallBack:
		call->type = &afs_SRXCBCallBack;
		return true;
	case CBInitCallBackState:
		call->type = &afs_SRXCBInitCallBackState;
		return true;
	case CBInitCallBackState3:
		call->type = &afs_SRXCBInitCallBackState3;
		return true;
	case CBProbe:
		call->type = &afs_SRXCBProbe;
		return true;
	case CBTellMeAboutYourself:
		call->type = &afs_SRXCBTellMeAboutYourself;
		return true;
	default:
		return false;
	}
}