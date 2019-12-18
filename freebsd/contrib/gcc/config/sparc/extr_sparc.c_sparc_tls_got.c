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
 int /*<<< orphan*/  Pmode ; 
 int current_function_uses_pic_offset_table ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ flag_pic ; 
 int /*<<< orphan*/  gen_reg_rtx (int /*<<< orphan*/ ) ; 
 scalar_t__ gen_rtx_SYMBOL_REF (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ global_offset_table ; 
 int /*<<< orphan*/  pic_offset_table_rtx ; 

__attribute__((used)) static rtx
sparc_tls_got (void)
{
  rtx temp;
  if (flag_pic)
    {
      current_function_uses_pic_offset_table = 1;
      return pic_offset_table_rtx;
    }

  if (!global_offset_table)
    global_offset_table = gen_rtx_SYMBOL_REF (Pmode, "_GLOBAL_OFFSET_TABLE_");
  temp = gen_reg_rtx (Pmode);
  emit_move_insn (temp, global_offset_table);
  return temp;
}