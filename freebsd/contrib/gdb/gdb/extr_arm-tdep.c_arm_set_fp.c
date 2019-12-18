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
struct gdbarch {int dummy; } ;
typedef  enum arm_float_model { ____Placeholder_arm_float_model } arm_float_model ;

/* Variables and functions */
 int ARM_FLOAT_FPA ; 
 int ARM_FLOAT_SOFT_FPA ; 
 scalar_t__ BFD_ENDIAN_LITTLE ; 
 int arm_get_fp_model (struct gdbarch*) ; 
 int /*<<< orphan*/  floatformat_ieee_double_little ; 
 int /*<<< orphan*/  floatformat_ieee_double_littlebyte_bigword ; 
 scalar_t__ gdbarch_byte_order (struct gdbarch*) ; 
 int /*<<< orphan*/  set_gdbarch_double_format (struct gdbarch*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_gdbarch_long_double_format (struct gdbarch*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
arm_set_fp (struct gdbarch *gdbarch)
{
  enum arm_float_model fp_model = arm_get_fp_model (gdbarch);

  if (gdbarch_byte_order (gdbarch) == BFD_ENDIAN_LITTLE 
      && (fp_model == ARM_FLOAT_SOFT_FPA || fp_model == ARM_FLOAT_FPA))
    {
      set_gdbarch_double_format	(gdbarch,
				 &floatformat_ieee_double_littlebyte_bigword);
      set_gdbarch_long_double_format
	(gdbarch, &floatformat_ieee_double_littlebyte_bigword);
    }
  else
    {
      set_gdbarch_double_format (gdbarch, &floatformat_ieee_double_little);
      set_gdbarch_long_double_format (gdbarch,
				      &floatformat_ieee_double_little);
    }
}