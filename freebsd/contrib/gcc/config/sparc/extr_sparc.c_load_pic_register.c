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
 int /*<<< orphan*/  ASM_GENERATE_INTERNAL_LABEL (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pmode ; 
 scalar_t__ TARGET_ARCH64 ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_pic_helper () ; 
 int flag_pic ; 
 int /*<<< orphan*/  gen_load_pcrel_symdi (int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  gen_load_pcrel_symsi (int /*<<< orphan*/ ,void*,void*) ; 
 void* gen_rtx_SYMBOL_REF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gen_rtx_USE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* global_offset_table ; 
 int /*<<< orphan*/  pic_helper_emitted_p ; 
 void* pic_helper_symbol ; 
 char* pic_helper_symbol_name ; 
 int /*<<< orphan*/  pic_offset_table_rtx ; 

__attribute__((used)) static void
load_pic_register (bool delay_pic_helper)
{
  int orig_flag_pic = flag_pic;

  /* If we haven't initialized the special PIC symbols, do so now.  */
  if (!pic_helper_symbol_name[0])
    {
      ASM_GENERATE_INTERNAL_LABEL (pic_helper_symbol_name, "LADDPC", 0);
      pic_helper_symbol = gen_rtx_SYMBOL_REF (Pmode, pic_helper_symbol_name);
      global_offset_table = gen_rtx_SYMBOL_REF (Pmode, "_GLOBAL_OFFSET_TABLE_");
    }

  /* If we haven't emitted the special PIC helper function, do so now unless
     we are requested to delay it.  */
  if (!delay_pic_helper && !pic_helper_emitted_p)
    emit_pic_helper ();

  flag_pic = 0;
  if (TARGET_ARCH64)
    emit_insn (gen_load_pcrel_symdi (pic_offset_table_rtx, global_offset_table,
				     pic_helper_symbol));
  else
    emit_insn (gen_load_pcrel_symsi (pic_offset_table_rtx, global_offset_table,
				     pic_helper_symbol));
  flag_pic = orig_flag_pic;

  /* Need to emit this whether or not we obey regdecls,
     since setjmp/longjmp can cause life info to screw up.
     ??? In the case where we don't obey regdecls, this is not sufficient
     since we may not fall out the bottom.  */
  emit_insn (gen_rtx_USE (VOIDmode, pic_offset_table_rtx));
}