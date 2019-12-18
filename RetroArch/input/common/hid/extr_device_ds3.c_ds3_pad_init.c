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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  hid_driver_t ;
struct TYPE_2__ {int /*<<< orphan*/  slot; } ;
typedef  TYPE_1__ ds3_instance_t ;

/* Variables and functions */

__attribute__((used)) static void *ds3_pad_init(void *data, uint32_t slot, hid_driver_t *driver)
{
   ds3_instance_t *pad = (ds3_instance_t *)data;
   pad->slot = slot;

   return data;
}