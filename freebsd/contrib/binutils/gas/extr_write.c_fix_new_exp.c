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
typedef  int /*<<< orphan*/  symbolS ;
typedef  int /*<<< orphan*/  offsetT ;
typedef  int /*<<< orphan*/  fragS ;
typedef  int /*<<< orphan*/  fixS ;
struct TYPE_4__ {int X_op; int /*<<< orphan*/  X_add_number; int /*<<< orphan*/ * X_add_symbol; int /*<<< orphan*/ * X_op_symbol; } ;
typedef  TYPE_1__ expressionS ;
typedef  int /*<<< orphan*/  RELOC_ENUM ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_RELOC_RVA ; 
#define  O_absent 135 
#define  O_add 134 
#define  O_constant 133 
#define  O_register 132 
#define  O_subtract 131 
#define  O_symbol 130 
#define  O_symbol_rva 129 
#define  O_uminus 128 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fix_new_internal (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * make_expr_symbol (TYPE_1__*) ; 

fixS *
fix_new_exp (fragS *frag,		/* Which frag?  */
	     int where,			/* Where in that frag?  */
	     int size,			/* 1, 2, or 4 usually.  */
	     expressionS *exp,		/* Expression.  */
	     int pcrel,			/* TRUE if PC-relative relocation.  */
	     RELOC_ENUM r_type		/* Relocation type.  */)
{
  symbolS *add = NULL;
  symbolS *sub = NULL;
  offsetT off = 0;

  switch (exp->X_op)
    {
    case O_absent:
      break;

    case O_register:
      as_bad (_("register value used as expression"));
      break;

    case O_add:
      /* This comes up when _GLOBAL_OFFSET_TABLE_+(.-L0) is read, if
	 the difference expression cannot immediately be reduced.  */
      {
	symbolS *stmp = make_expr_symbol (exp);

	exp->X_op = O_symbol;
	exp->X_op_symbol = 0;
	exp->X_add_symbol = stmp;
	exp->X_add_number = 0;

	return fix_new_exp (frag, where, size, exp, pcrel, r_type);
      }

    case O_symbol_rva:
      add = exp->X_add_symbol;
      off = exp->X_add_number;
      r_type = BFD_RELOC_RVA;
      break;

    case O_uminus:
      sub = exp->X_add_symbol;
      off = exp->X_add_number;
      break;

    case O_subtract:
      sub = exp->X_op_symbol;
      /* Fall through.  */
    case O_symbol:
      add = exp->X_add_symbol;
      /* Fall through.  */
    case O_constant:
      off = exp->X_add_number;
      break;

    default:
      add = make_expr_symbol (exp);
      break;
    }

  return fix_new_internal (frag, where, size, add, sub, off, pcrel, r_type);
}