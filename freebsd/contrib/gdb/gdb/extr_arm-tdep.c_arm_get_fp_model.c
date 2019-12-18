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
struct gdbarch {int dummy; } ;
typedef  enum arm_float_model { ____Placeholder_arm_float_model } arm_float_model ;
struct TYPE_2__ {int fp_model; } ;

/* Variables and functions */
 scalar_t__ ARM_FLOAT_AUTO ; 
 scalar_t__ arm_fp_model ; 
 TYPE_1__* gdbarch_tdep (struct gdbarch*) ; 

enum arm_float_model
arm_get_fp_model (struct gdbarch *gdbarch)
{
  if (arm_fp_model == ARM_FLOAT_AUTO)
    return gdbarch_tdep (gdbarch)->fp_model;

  return arm_fp_model;
}