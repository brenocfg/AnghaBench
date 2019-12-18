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

/* Variables and functions */
 void** record_drivers ; 

__attribute__((used)) static const void *record_driver_find_handle(int idx)
{
   const void *drv = record_drivers[idx];
   if (!drv)
      return NULL;
   return drv;
}