#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_STATUS ;
typedef  int /*<<< orphan*/  tBTM_CMPL_CB ;
struct TYPE_3__ {int /*<<< orphan*/  rln_timer; int /*<<< orphan*/ * p_rln_cmpl_cb; } ;
struct TYPE_4__ {TYPE_1__ devcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_CMD_STARTED ; 
 int /*<<< orphan*/  BTM_DEV_REPLY_TIMEOUT ; 
 int /*<<< orphan*/  BTM_NO_RESOURCES ; 
 int /*<<< orphan*/  BTU_TTYPE_BTM_DEV_CTL ; 
 TYPE_2__ btm_cb ; 
 int /*<<< orphan*/  btsnd_hcic_read_name () ; 
 int /*<<< orphan*/  btu_start_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tBTM_STATUS BTM_ReadLocalDeviceNameFromController (tBTM_CMPL_CB *p_rln_cmpl_cback)
{
    /* Check if rln already in progress */
    if (btm_cb.devcb.p_rln_cmpl_cb) {
        return (BTM_NO_RESOURCES);
    }

    /* Save callback */
    btm_cb.devcb.p_rln_cmpl_cb = p_rln_cmpl_cback;

    btsnd_hcic_read_name();
    btu_start_timer (&btm_cb.devcb.rln_timer, BTU_TTYPE_BTM_DEV_CTL, BTM_DEV_REPLY_TIMEOUT);

    return BTM_CMD_STARTED;
}