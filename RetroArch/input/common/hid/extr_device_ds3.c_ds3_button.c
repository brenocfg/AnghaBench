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
typedef  int uint16_t ;
struct TYPE_2__ {int buttons; } ;
typedef  TYPE_1__ ds3_instance_t ;

/* Variables and functions */

__attribute__((used)) static bool ds3_button(void *data, uint16_t joykey)
{
   ds3_instance_t *pad = (ds3_instance_t *)data;
   if(!pad || joykey > 31)
      return false;

   return pad->buttons & (1 << joykey);
}