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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ DECIMAL_FLOAT_MODE_P (int) ; 
 int default_scalar_mode_supported_p (int) ; 

__attribute__((used)) static bool
s390_scalar_mode_supported_p (enum machine_mode mode)
{
  if (DECIMAL_FLOAT_MODE_P (mode))
    return true;
  else
    return default_scalar_mode_supported_p (mode);
}