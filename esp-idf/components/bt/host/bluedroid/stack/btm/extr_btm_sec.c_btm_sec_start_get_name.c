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
struct TYPE_3__ {int /*<<< orphan*/  sec_state; int /*<<< orphan*/  bd_addr; } ;
typedef  TYPE_1__ tBTM_SEC_DEV_REC ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ BTM_CMD_STARTED ; 
 int /*<<< orphan*/  BTM_RMT_NAME_SEC ; 
 int /*<<< orphan*/  BTM_SEC_STATE_GETTING_NAME ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ btm_initiate_rem_name (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOLEAN btm_sec_start_get_name (tBTM_SEC_DEV_REC *p_dev_rec)
{
    UINT8 tempstate = p_dev_rec->sec_state;

    p_dev_rec->sec_state = BTM_SEC_STATE_GETTING_NAME;

    /* Device should be connected, no need to provide correct page params */
    /* 0 and NULL are as timeout and callback params because they are not used in security get name case */
    if ((btm_initiate_rem_name (p_dev_rec->bd_addr, NULL, BTM_RMT_NAME_SEC,
                                0, NULL)) != BTM_CMD_STARTED) {
        p_dev_rec->sec_state = tempstate;
        return (FALSE);
    }

    return (TRUE);
}