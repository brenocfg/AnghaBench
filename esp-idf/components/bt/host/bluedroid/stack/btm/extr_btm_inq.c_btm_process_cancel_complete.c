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
typedef  int /*<<< orphan*/  UINT8 ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_BLI_INQ_CANCEL_EVT ; 
 int /*<<< orphan*/  btm_acl_update_busy_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_process_inq_complete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void btm_process_cancel_complete(UINT8 status, UINT8 mode)
{
    btm_acl_update_busy_level (BTM_BLI_INQ_CANCEL_EVT);
    btm_process_inq_complete(status, mode);
}