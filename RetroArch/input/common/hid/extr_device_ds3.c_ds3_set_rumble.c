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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  enum retro_rumble_effect { ____Placeholder_retro_rumble_effect } retro_rumble_effect ;
typedef  int /*<<< orphan*/  ds3_instance_t ;

/* Variables and functions */

__attribute__((used)) static void ds3_set_rumble(void *data, enum retro_rumble_effect effect, uint16_t strength)
{
   ds3_instance_t *pad = (ds3_instance_t *)data;
}