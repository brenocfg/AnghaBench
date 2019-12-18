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
typedef  int /*<<< orphan*/  tBTM_PM_STATUS ;
struct TYPE_4__ {int /*<<< orphan*/  event; } ;
struct TYPE_5__ {int /*<<< orphan*/  bd_addr; int /*<<< orphan*/  hci_status; int /*<<< orphan*/  value; int /*<<< orphan*/  status; TYPE_1__ hdr; } ;
typedef  TYPE_2__ tBTA_DM_PM_BTM_STATUS ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DM_PM_BTM_STATUS_EVT ; 
 int /*<<< orphan*/  bdcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_2__*) ; 
 scalar_t__ osi_malloc (int) ; 

__attribute__((used)) static void bta_dm_pm_btm_cback(BD_ADDR bd_addr, tBTM_PM_STATUS status, UINT16 value, UINT8 hci_status)
{
    tBTA_DM_PM_BTM_STATUS  *p_buf;

    if ((p_buf = (tBTA_DM_PM_BTM_STATUS *) osi_malloc(sizeof(tBTA_DM_PM_BTM_STATUS))) != NULL) {
        p_buf->hdr.event = BTA_DM_PM_BTM_STATUS_EVT;
        p_buf->status = status;
        p_buf->value = value;
        p_buf->hci_status = hci_status;
        bdcpy(p_buf->bd_addr, bd_addr);
        bta_sys_sendmsg(p_buf);
    }
}