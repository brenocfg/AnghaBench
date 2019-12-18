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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  ASM_GENERATE_INTERNAL_LABEL (char*,char*,int) ; 
 int /*<<< orphan*/  LCT_NORMAL ; 
 int /*<<< orphan*/  MCOUNT_FUNCTION ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  emit_library_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SYMBOL_REF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ggc_strdup (char*) ; 

void
sparc_profile_hook (int labelno)
{
  char buf[32];
  rtx lab, fun;

  ASM_GENERATE_INTERNAL_LABEL (buf, "LP", labelno);
  lab = gen_rtx_SYMBOL_REF (Pmode, ggc_strdup (buf));
  fun = gen_rtx_SYMBOL_REF (Pmode, MCOUNT_FUNCTION);

  emit_library_call (fun, LCT_NORMAL, VOIDmode, 1, lab, Pmode);
}