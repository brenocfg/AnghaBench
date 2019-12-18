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
 scalar_t__ GET_MODE_SIZE (int) ; 
 scalar_t__ INTVAL (scalar_t__) ; 
 int /*<<< orphan*/  MEM_P (scalar_t__) ; 
 scalar_t__ MEM_SIZE (scalar_t__) ; 

bool
mips_mem_fits_mode_p (enum machine_mode mode, rtx x)
{
  rtx size;

  if (!MEM_P (x))
    return false;

  size = MEM_SIZE (x);
  return size && INTVAL (size) == GET_MODE_SIZE (mode);
}