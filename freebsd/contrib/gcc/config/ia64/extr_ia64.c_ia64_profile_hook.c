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
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_2__ {char* (* strip_name_encoding ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  SYMBOL_REF_FLAGS ;

/* Variables and functions */
 int /*<<< orphan*/  ASM_GENERATE_INTERNAL_LABEL (char*,char*,int) ; 
 int /*<<< orphan*/  BR_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCT_NORMAL ; 
 scalar_t__ NO_PROFILE_COUNTERS ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  SYMBOL_FLAG_LOCAL ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_library_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_ip_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_mcount_func_rtx () ; 
 int /*<<< orphan*/  gen_reg_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SYMBOL_REF (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ggc_strdup (char*) ; 
 char* stub1 (int /*<<< orphan*/ ) ; 
 TYPE_1__ targetm ; 

void
ia64_profile_hook (int labelno)
{
  rtx label, ip;

  if (NO_PROFILE_COUNTERS)
    label = const0_rtx;
  else
    {
      char buf[30];
      const char *label_name;
      ASM_GENERATE_INTERNAL_LABEL (buf, "LP", labelno);
      label_name = (*targetm.strip_name_encoding) (ggc_strdup (buf));
      label = gen_rtx_SYMBOL_REF (Pmode, label_name);
      SYMBOL_REF_FLAGS (label) = SYMBOL_FLAG_LOCAL;
    }
  ip = gen_reg_rtx (Pmode);
  emit_insn (gen_ip_value (ip));
  emit_library_call (gen_mcount_func_rtx (), LCT_NORMAL,
                     VOIDmode, 3,
		     gen_rtx_REG (Pmode, BR_REG (0)), Pmode,
		     ip, Pmode,
		     label, Pmode);
}