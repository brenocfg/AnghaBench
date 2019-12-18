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
struct TYPE_2__ {int is_element; } ;
typedef  TYPE_1__ rcheevos_deactivate_t ;

/* Variables and functions */

__attribute__((used)) static int rcheevos_deactivate_index(void* userdata, unsigned int index)
{
   rcheevos_deactivate_t* ud = (rcheevos_deactivate_t*)userdata;

   ud->is_element           = 1;
   return 0;
}