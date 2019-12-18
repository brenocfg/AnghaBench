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
 int /*<<< orphan*/  TARGET_AAPCS_BASED ; 

__attribute__((used)) static bool
arm_cxx_class_data_always_comdat (void)
{
  /* \S 3.2.5.4 of the ARM C++ ABI says that class data only have
     vague linkage if the class has no key function.  */
  return !TARGET_AAPCS_BASED;
}