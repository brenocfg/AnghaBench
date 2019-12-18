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
typedef  enum mips_symbol_type { ____Placeholder_mips_symbol_type } mips_symbol_type ;
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  UNSPEC_ADDRESS (int /*<<< orphan*/ ) ; 
 scalar_t__ UNSPEC_ADDRESS_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal_insn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ *) ; 
 int mips_classify_symbolic_expression (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_split_const (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  output_addr_const (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plus_constant (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_operand_reloc (FILE *file, rtx op, const char **relocs)
{
  enum mips_symbol_type symbol_type;
  const char *p;
  rtx base;
  HOST_WIDE_INT offset;

  symbol_type = mips_classify_symbolic_expression (op);
  if (relocs[symbol_type] == 0)
    fatal_insn ("PRINT_OPERAND, invalid operand for relocation", op);

  /* If OP uses an UNSPEC address, we want to print the inner symbol.  */
  mips_split_const (op, &base, &offset);
  if (UNSPEC_ADDRESS_P (base))
    op = plus_constant (UNSPEC_ADDRESS (base), offset);

  fputs (relocs[symbol_type], file);
  output_addr_const (file, op);
  for (p = relocs[symbol_type]; *p != 0; p++)
    if (*p == '(')
      fputc (')', file);
}