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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  ble_resolving_list_max_size; int /*<<< orphan*/  ble_supported; int /*<<< orphan*/  readable; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__ controller_param ; 

__attribute__((used)) static uint8_t get_ble_resolving_list_max_size(void)
{
    assert(controller_param.readable);
    assert(controller_param.ble_supported);
    return controller_param.ble_resolving_list_max_size;
}