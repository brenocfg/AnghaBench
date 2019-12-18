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
typedef  int /*<<< orphan*/  tBTA_HF_CLIENT_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  BTA_HF_CLIENT_API_DEREGISTER_EVT ; 
 int /*<<< orphan*/  BTA_ID_HS ; 
 int /*<<< orphan*/  bta_hf_client_sm_execute (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bta_sys_collision_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bta_sys_deregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_sys_is_register (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bta_hf_client_api_disable(tBTA_HF_CLIENT_DATA *p_data)
{
    if (!bta_sys_is_register (BTA_ID_HS)) {
        APPL_TRACE_ERROR("BTA HF Client is already disabled, ignoring ...");
        return;
    }

    /* De-register with BTA system manager */
    bta_sys_deregister(BTA_ID_HS);

    bta_hf_client_sm_execute(BTA_HF_CLIENT_API_DEREGISTER_EVT, p_data);

    bta_sys_collision_register (BTA_ID_HS, NULL);
}