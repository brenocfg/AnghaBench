#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTA_UPDATE_DUPLICATE_EXCEPTIONAL_LIST_CMPL_CBACK ;
struct TYPE_4__ {int /*<<< orphan*/  event; } ;
struct TYPE_5__ {int /*<<< orphan*/  device_info; int /*<<< orphan*/  exceptional_list_cb; int /*<<< orphan*/  type; int /*<<< orphan*/  subcode; TYPE_1__ hdr; } ;
typedef  TYPE_2__ tBTA_DM_API_UPDATE_DUPLICATE_EXCEPTIONAL_LIST ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DM_API_UPDATE_DUPLICATE_EXCEPTIONAL_LIST_EVT ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ osi_malloc (int) ; 

void BTA_DmUpdateDuplicateExceptionalList(UINT8 subcode, UINT32 type, BD_ADDR device_info, tBTA_UPDATE_DUPLICATE_EXCEPTIONAL_LIST_CMPL_CBACK p_update_duplicate_exceptional_list_cback)
{
    tBTA_DM_API_UPDATE_DUPLICATE_EXCEPTIONAL_LIST *p_msg;
    if ((p_msg = (tBTA_DM_API_UPDATE_DUPLICATE_EXCEPTIONAL_LIST *)osi_malloc(sizeof(tBTA_DM_API_UPDATE_DUPLICATE_EXCEPTIONAL_LIST))) != NULL) {
        p_msg->hdr.event = BTA_DM_API_UPDATE_DUPLICATE_EXCEPTIONAL_LIST_EVT;
        p_msg->subcode = subcode;
        p_msg->type = type;
        p_msg->exceptional_list_cb = p_update_duplicate_exceptional_list_cback;
        memcpy(p_msg->device_info, device_info, sizeof(BD_ADDR));

        bta_sys_sendmsg(p_msg);
    }
}