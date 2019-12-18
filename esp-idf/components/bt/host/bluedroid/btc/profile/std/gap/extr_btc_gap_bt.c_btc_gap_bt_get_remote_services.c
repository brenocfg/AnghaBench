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
struct TYPE_3__ {int /*<<< orphan*/  address; } ;
typedef  TYPE_1__ bt_bdaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_ALL_SERVICE_MASK ; 
 int /*<<< orphan*/  BTA_DmDiscover (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bte_dm_search_services_evt ; 

__attribute__((used)) static void btc_gap_bt_get_remote_services(bt_bdaddr_t *remote_bda)
{
    BTA_DmDiscover(remote_bda->address, BTA_ALL_SERVICE_MASK,
                   bte_dm_search_services_evt, TRUE);
}