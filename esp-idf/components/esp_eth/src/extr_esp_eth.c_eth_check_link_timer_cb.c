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
struct TYPE_4__ {int /*<<< orphan*/  (* get_link ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ esp_eth_phy_t ;
struct TYPE_5__ {TYPE_1__* phy; } ;
typedef  TYPE_2__ esp_eth_driver_t ;
typedef  int /*<<< orphan*/  TimerHandle_t ;

/* Variables and functions */
 scalar_t__ pvTimerGetTimerID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void eth_check_link_timer_cb(TimerHandle_t xTimer)
{
    esp_eth_driver_t *eth_driver = (esp_eth_driver_t *)pvTimerGetTimerID(xTimer);
    esp_eth_phy_t *phy = eth_driver->phy;
    phy->get_link(phy);
}