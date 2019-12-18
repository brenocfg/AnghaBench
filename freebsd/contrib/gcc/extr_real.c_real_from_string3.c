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
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;

/* Variables and functions */
 scalar_t__ DECIMAL_FLOAT_MODE_P (int) ; 
 int VOIDmode ; 
 int /*<<< orphan*/  decimal_real_from_string (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  real_convert (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  real_from_string (int /*<<< orphan*/ *,char const*) ; 

void 
real_from_string3 (REAL_VALUE_TYPE *r, const char *s, enum machine_mode mode)
{
  if (DECIMAL_FLOAT_MODE_P (mode))
    decimal_real_from_string (r, s);
  else
    real_from_string (r, s);

  if (mode != VOIDmode)
    real_convert (r, mode, r);  
}