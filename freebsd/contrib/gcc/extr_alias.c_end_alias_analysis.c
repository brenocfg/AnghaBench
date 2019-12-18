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
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  ggc_free (scalar_t__) ; 
 int /*<<< orphan*/  old_reg_base_value ; 
 int /*<<< orphan*/  reg_base_value ; 
 scalar_t__ reg_known_equiv_p ; 
 scalar_t__ reg_known_value ; 
 scalar_t__ reg_known_value_size ; 

void
end_alias_analysis (void)
{
  old_reg_base_value = reg_base_value;
  ggc_free (reg_known_value);
  reg_known_value = 0;
  reg_known_value_size = 0;
  free (reg_known_equiv_p);
  reg_known_equiv_p = 0;
}