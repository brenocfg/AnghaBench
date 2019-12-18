#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fragS ;
struct TYPE_8__ {int /*<<< orphan*/  tc_fix_data; } ;
typedef  TYPE_1__ fixS ;
struct TYPE_9__ {int X_op; } ;
typedef  TYPE_2__ expressionS ;

/* Variables and functions */
#define  O_add 131 
#define  O_constant 130 
#define  O_subtract 129 
#define  O_symbol 128 
 TYPE_1__* fix_new (int /*<<< orphan*/ *,int,short,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__* fix_new_exp (int /*<<< orphan*/ *,int,short,TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  make_expr_symbol (TYPE_2__*) ; 
 int /*<<< orphan*/  thumb_mode ; 

__attribute__((used)) static void
fix_new_arm (fragS *	   frag,
	     int	   where,
	     short int	   size,
	     expressionS * exp,
	     int	   pc_rel,
	     int	   reloc)
{
  fixS *	   new_fix;

  switch (exp->X_op)
    {
    case O_constant:
    case O_symbol:
    case O_add:
    case O_subtract:
      new_fix = fix_new_exp (frag, where, size, exp, pc_rel, reloc);
      break;

    default:
      new_fix = fix_new (frag, where, size, make_expr_symbol (exp), 0,
			 pc_rel, reloc);
      break;
    }

  /* Mark whether the fix is to a THUMB instruction, or an ARM
     instruction.  */
  new_fix->tc_fix_data = thumb_mode;
}