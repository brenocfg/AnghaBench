#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ X_op; int X_add_number; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT ; 
 int /*<<< orphan*/  BFD_RELOC_LO16 ; 
 int /*<<< orphan*/  HAVE_64BIT_GPRS ; 
 scalar_t__ O_constant ; 
 TYPE_1__ imm_expr ; 
 int /*<<< orphan*/  load_register (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macro_build (TYPE_1__*,char*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_at (int reg, int unsignedp)
{
  if (imm_expr.X_op == O_constant
      && imm_expr.X_add_number >= -0x8000
      && imm_expr.X_add_number < 0x8000)
    macro_build (&imm_expr, unsignedp ? "sltiu" : "slti", "t,r,j",
		 AT, reg, BFD_RELOC_LO16);
  else
    {
      load_register (AT, &imm_expr, HAVE_64BIT_GPRS);
      macro_build (NULL, unsignedp ? "sltu" : "slt", "d,v,t", AT, reg, AT);
    }
}