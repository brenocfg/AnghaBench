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
 int parameter_reset ; 
 int /*<<< orphan*/  vcos_assert (int*) ; 

__attribute__((used)) static int update_cycle_parameter(int *option, int min, int max, int increment)
{
   vcos_assert(option);
   if (!option)
      return 0;

   if (*option == parameter_reset)
      *option = min - increment;

   *option += increment;

   if (*option > max)
   {
      *option = parameter_reset;
      return 0;
   }
   else
      return 1;
}