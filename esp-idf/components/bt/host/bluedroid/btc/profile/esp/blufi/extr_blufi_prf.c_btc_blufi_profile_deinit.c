#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tGATT_STATUS ;
struct TYPE_2__ {int /*<<< orphan*/  gatt_if; int /*<<< orphan*/  handle_srvc; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_GATTS_AppDeregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTA_GATTS_DeleteService (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTA_GATTS_StopService (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTC_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  GATT_ERROR ; 
 int /*<<< orphan*/  GATT_SUCCESS ; 
 TYPE_1__ blufi_env ; 

__attribute__((used)) static tGATT_STATUS btc_blufi_profile_deinit(void)
{
    if (!blufi_env.enabled) {
        BTC_TRACE_ERROR("BLUFI already de-initialized");
        return GATT_ERROR;
    }

    BTA_GATTS_StopService(blufi_env.handle_srvc);
    BTA_GATTS_DeleteService(blufi_env.handle_srvc);
    /* register the BLUFI profile to the BTA_GATTS module*/
    BTA_GATTS_AppDeregister(blufi_env.gatt_if);

    return GATT_SUCCESS;
}