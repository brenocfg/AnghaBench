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
 int GET_MODE (scalar_t__) ; 
 int /*<<< orphan*/  MEM_COPY_ATTRIBUTES (scalar_t__,scalar_t__) ; 
 scalar_t__ MEM_P (scalar_t__) ; 
 int VOIDmode ; 
 scalar_t__ XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 
 scalar_t__ gen_rtx_MEM (int,scalar_t__) ; 
 scalar_t__ memory_address (int,scalar_t__) ; 
 scalar_t__ memory_address_p (int,scalar_t__) ; 
 scalar_t__ reload_completed ; 
 scalar_t__ reload_in_progress ; 
 scalar_t__ rtx_equal_p (scalar_t__,scalar_t__) ; 

__attribute__((used)) static rtx
change_address_1 (rtx memref, enum machine_mode mode, rtx addr, int validate)
{
  rtx new;

  gcc_assert (MEM_P (memref));
  if (mode == VOIDmode)
    mode = GET_MODE (memref);
  if (addr == 0)
    addr = XEXP (memref, 0);
  if (mode == GET_MODE (memref) && addr == XEXP (memref, 0)
      && (!validate || memory_address_p (mode, addr)))
    return memref;

  if (validate)
    {
      if (reload_in_progress || reload_completed)
	gcc_assert (memory_address_p (mode, addr));
      else
	addr = memory_address (mode, addr);
    }

  if (rtx_equal_p (addr, XEXP (memref, 0)) && mode == GET_MODE (memref))
    return memref;

  new = gen_rtx_MEM (mode, addr);
  MEM_COPY_ATTRIBUTES (new, memref);
  return new;
}