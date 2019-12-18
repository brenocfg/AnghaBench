#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  event; } ;
struct TYPE_6__ {int /*<<< orphan*/  icon; TYPE_1__ hdr; } ;
typedef  TYPE_2__ tBTA_DM_API_LOCAL_ICON ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DM_API_LOCAL_ICON_EVT ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ osi_malloc (int) ; 

void BTA_DmBleConfigLocalIcon(uint16_t icon)
{
    tBTA_DM_API_LOCAL_ICON *p_msg;

    if ((p_msg = (tBTA_DM_API_LOCAL_ICON *) osi_malloc(sizeof(tBTA_DM_API_LOCAL_ICON))) != NULL) {
        memset (p_msg, 0, sizeof(tBTA_DM_API_LOCAL_ICON));

        p_msg->hdr.event = BTA_DM_API_LOCAL_ICON_EVT;
        p_msg->icon   = icon;
        bta_sys_sendmsg(p_msg);
    }
}