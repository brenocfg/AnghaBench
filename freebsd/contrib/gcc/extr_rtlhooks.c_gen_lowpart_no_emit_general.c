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
typedef  scalar_t__ rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ gen_lowpart_if_possible (int,scalar_t__) ; 

rtx
gen_lowpart_no_emit_general (enum machine_mode mode, rtx x)
{
  rtx result = gen_lowpart_if_possible (mode, x);
  if (result)
    return result;
  else
    return x;
}