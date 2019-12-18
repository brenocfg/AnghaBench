#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tSMP_STATUS ;
struct TYPE_3__ {int /*<<< orphan*/  sec_flags; } ;
typedef  TYPE_1__ tBTM_SEC_DEV_REC ;
typedef  scalar_t__ UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_SEC_LE_AUTHENTICATED ; 
 scalar_t__ BTM_SUCCESS ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  BTM_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  SMP_PASSKEY_ENTRY_FAIL ; 
 int /*<<< orphan*/  SMP_PasskeyReply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMP_SUCCESS ; 
 TYPE_1__* btm_find_dev (int /*<<< orphan*/ ) ; 

void BTM_BlePasskeyReply (BD_ADDR bd_addr, UINT8 res, UINT32 passkey)
{
#if SMP_INCLUDED == TRUE
    tBTM_SEC_DEV_REC  *p_dev_rec = btm_find_dev (bd_addr);
    tSMP_STATUS      res_smp = (res == BTM_SUCCESS) ? SMP_SUCCESS : SMP_PASSKEY_ENTRY_FAIL;

    if (p_dev_rec == NULL) {
        BTM_TRACE_ERROR("Passkey reply to Unknown device");
        return;
    }

    p_dev_rec->sec_flags   |= BTM_SEC_LE_AUTHENTICATED;
    BTM_TRACE_DEBUG ("BTM_BlePasskeyReply");
    SMP_PasskeyReply(bd_addr, res_smp, passkey);
#endif
}