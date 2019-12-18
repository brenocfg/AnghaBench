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
typedef  int /*<<< orphan*/  ds3_instance_t ;

/* Variables and functions */

__attribute__((used)) static const char *ds3_get_name(void *data)
{
   ds3_instance_t *pad = (ds3_instance_t *)data;
   return "Sony DualShock 3";
}