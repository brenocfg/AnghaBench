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
typedef  int /*<<< orphan*/  bt_device_features_t ;
struct TYPE_2__ {int /*<<< orphan*/  const features_ble; int /*<<< orphan*/  ble_supported; int /*<<< orphan*/  readable; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__ controller_param ; 

__attribute__((used)) static const bt_device_features_t *get_features_ble(void)
{
    assert(controller_param.readable);
    assert(controller_param.ble_supported);
    return &controller_param.features_ble;
}