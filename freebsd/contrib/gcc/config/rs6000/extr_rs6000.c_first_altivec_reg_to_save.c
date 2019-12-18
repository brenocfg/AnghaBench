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
 scalar_t__ ABI_DARWIN ; 
 scalar_t__ DEFAULT_ABI ; 
 int FIRST_ALTIVEC_REGNO ; 
 int LAST_ALTIVEC_REGNO ; 
 int /*<<< orphan*/  TARGET_ALTIVEC ; 
 int /*<<< orphan*/  TARGET_ALTIVEC_ABI ; 
 scalar_t__ current_function_calls_eh_return ; 
 scalar_t__* regs_ever_live ; 

__attribute__((used)) static int
first_altivec_reg_to_save (void)
{
  int i;

  /* Stack frame remains as is unless we are in AltiVec ABI.  */
  if (! TARGET_ALTIVEC_ABI)
    return LAST_ALTIVEC_REGNO + 1;

  /* On Darwin, the unwind routines are compiled without
     TARGET_ALTIVEC, and use save_world to save/restore the 
     altivec registers when necessary.  */
  if (DEFAULT_ABI == ABI_DARWIN && current_function_calls_eh_return
      && ! TARGET_ALTIVEC)
    return FIRST_ALTIVEC_REGNO + 20;

  /* Find lowest numbered live register.  */
  for (i = FIRST_ALTIVEC_REGNO + 20; i <= LAST_ALTIVEC_REGNO; ++i)
    if (regs_ever_live[i])
      break;

  return i;
}