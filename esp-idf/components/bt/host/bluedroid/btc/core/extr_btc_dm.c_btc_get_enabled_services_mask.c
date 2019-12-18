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
typedef  int /*<<< orphan*/  tBTA_SERVICE_MASK ;
struct TYPE_2__ {int /*<<< orphan*/  btc_enabled_services; } ;

/* Variables and functions */
 TYPE_1__ btc_dm_cb ; 

tBTA_SERVICE_MASK btc_get_enabled_services_mask(void)
{
    return btc_dm_cb.btc_enabled_services;
}