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
 int /*<<< orphan*/  cgen_clear_signed_overflow_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgen_set_signed_overflow_ok (int /*<<< orphan*/ ) ; 
 scalar_t__ flag_signed_overflow_ok ; 
 int /*<<< orphan*/  gas_cgen_cpu_desc ; 

void
gas_cgen_begin ()
{
  if (flag_signed_overflow_ok)
    cgen_set_signed_overflow_ok (gas_cgen_cpu_desc);
  else
    cgen_clear_signed_overflow_ok (gas_cgen_cpu_desc);
}