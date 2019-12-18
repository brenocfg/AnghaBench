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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  ASM_DECLARE_CONSTANT_NAME (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASM_OUTPUT_LABEL (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  asm_out_file ; 
 int /*<<< orphan*/  get_constant_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_constant (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void
assemble_constant_contents (tree exp, const char *label, unsigned int align)
{
  HOST_WIDE_INT size;

  size = get_constant_size (exp);

  /* Do any machine/system dependent processing of the constant.  */
#ifdef ASM_DECLARE_CONSTANT_NAME
  ASM_DECLARE_CONSTANT_NAME (asm_out_file, label, exp, size);
#else
  /* Standard thing is just output label for the constant.  */
  ASM_OUTPUT_LABEL (asm_out_file, label);
#endif /* ASM_DECLARE_CONSTANT_NAME */

  /* Output the value of EXP.  */
  output_constant (exp, size, align);
}