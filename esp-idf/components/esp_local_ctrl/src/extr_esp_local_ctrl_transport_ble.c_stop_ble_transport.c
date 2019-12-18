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
typedef  int /*<<< orphan*/  protocomm_t ;

/* Variables and functions */
 int /*<<< orphan*/  protocomm_ble_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stop_ble_transport(protocomm_t *pc)
{
    protocomm_ble_stop(pc);
}