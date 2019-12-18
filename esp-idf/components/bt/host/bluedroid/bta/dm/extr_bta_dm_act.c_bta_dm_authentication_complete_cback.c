#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int fail_reason; int /*<<< orphan*/  addr_type; int /*<<< orphan*/  dev_type; scalar_t__* bd_name; int /*<<< orphan*/  bd_addr; } ;
struct TYPE_7__ {TYPE_1__ auth_cmpl; } ;
typedef  TYPE_2__ tBTA_DM_SEC ;
typedef  int UINT8 ;
struct TYPE_8__ {int /*<<< orphan*/  (* p_sec_cback ) (int /*<<< orphan*/ ,TYPE_2__*) ;} ;
typedef  int /*<<< orphan*/  DEV_CLASS ;
typedef  int /*<<< orphan*/  BD_NAME ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int BD_NAME_LEN ; 
 int /*<<< orphan*/  BTA_DM_AUTH_CMPL_EVT ; 
 int /*<<< orphan*/  BTM_ReadDevInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int BTM_SUCCESS ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__ bta_dm_cb ; 
 int /*<<< orphan*/  bta_dm_remove_sec_dev_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static UINT8 bta_dm_authentication_complete_cback(BD_ADDR bd_addr, DEV_CLASS dev_class, BD_NAME bd_name, int result)
{
    tBTA_DM_SEC sec_event;
    UNUSED(dev_class);

    if (result != BTM_SUCCESS) {
        memset(&sec_event, 0, sizeof(tBTA_DM_SEC));
        bdcpy(sec_event.auth_cmpl.bd_addr, bd_addr);

        memcpy(sec_event.auth_cmpl.bd_name, bd_name, (BD_NAME_LEN - 1));
        sec_event.auth_cmpl.bd_name[BD_NAME_LEN - 1] = 0;

#if BLE_INCLUDED == TRUE
        // Report the BR link key based on the BR/EDR address and type
        BTM_ReadDevInfo(bd_addr, &sec_event.auth_cmpl.dev_type, &sec_event.auth_cmpl.addr_type);
#endif
        sec_event.auth_cmpl.fail_reason = (UINT8)result;

        if (bta_dm_cb.p_sec_cback) {
            bta_dm_cb.p_sec_cback(BTA_DM_AUTH_CMPL_EVT, &sec_event);
        }

        bta_dm_remove_sec_dev_entry(bd_addr);
    }

    return BTM_SUCCESS;
}