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
struct dwarf_expr_baton {int /*<<< orphan*/  frame; } ;
typedef  enum lval_type { ____Placeholder_lval_type } lval_type ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int DWARF2_REG_TO_REGNUM (int) ; 
 scalar_t__ alloca (int) ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/  extract_unsigned_integer (char*,int) ; 
 int /*<<< orphan*/  frame_register (int /*<<< orphan*/ ,int,int*,int*,int /*<<< orphan*/ *,int*,char*) ; 
 int register_size (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static CORE_ADDR
dwarf_expr_read_reg (void *baton, int dwarf_regnum)
{
  struct dwarf_expr_baton *debaton = (struct dwarf_expr_baton *) baton;
  CORE_ADDR result, save_addr;
  enum lval_type lval_type;
  char *buf;
  int optimized, regnum, realnum, regsize;

  regnum = DWARF2_REG_TO_REGNUM (dwarf_regnum);
  regsize = register_size (current_gdbarch, regnum);
  buf = (char *) alloca (regsize);

  frame_register (debaton->frame, regnum, &optimized, &lval_type, &save_addr,
		  &realnum, buf);
  /* NOTE: cagney/2003-05-22: This extract is assuming that a DWARF 2
     address is always unsigned.  That may or may not be true.  */
  result = extract_unsigned_integer (buf, regsize);

  return result;
}