#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  valueT ;
struct TYPE_10__ {int X_op; int /*<<< orphan*/  X_add_number; TYPE_2__* X_add_symbol; } ;
struct TYPE_9__ {int sy_resolving; int /*<<< orphan*/ * sy_frag; TYPE_1__* bsym; int /*<<< orphan*/  sy_resolved; TYPE_3__ sy_value; } ;
typedef  TYPE_2__ symbolS ;
struct local_symbol {scalar_t__ lsy_section; int /*<<< orphan*/  lsy_value; } ;
typedef  scalar_t__ segT ;
typedef  int /*<<< orphan*/  fragS ;
typedef  TYPE_3__ expressionS ;
struct TYPE_8__ {scalar_t__ section; } ;

/* Variables and functions */
 scalar_t__ LOCAL_SYMBOL_CHECK (TYPE_2__*) ; 
#define  O_constant 131 
 int O_illegal ; 
#define  O_register 130 
#define  O_symbol 129 
#define  O_symbol_rva 128 
 scalar_t__ absolute_section ; 
 scalar_t__ expr_section ; 
 int /*<<< orphan*/ * local_symbol_get_frag (struct local_symbol*) ; 
 scalar_t__ reg_section ; 
 int resolve_expression (TYPE_3__*) ; 
 int /*<<< orphan*/  symbol_equated_p (TYPE_2__*) ; 
 scalar_t__ undefined_section ; 

int
snapshot_symbol (symbolS **symbolPP, valueT *valueP, segT *segP, fragS **fragPP)
{
  symbolS *symbolP = *symbolPP;

  if (LOCAL_SYMBOL_CHECK (symbolP))
    {
      struct local_symbol *locsym = (struct local_symbol *) symbolP;

      *valueP = locsym->lsy_value;
      *segP = locsym->lsy_section;
      *fragPP = local_symbol_get_frag (locsym);
    }
  else
    {
      expressionS expr = symbolP->sy_value;

      if (!symbolP->sy_resolved && expr.X_op != O_illegal)
	{
	  int resolved;

	  if (symbolP->sy_resolving)
	    return 0;
	  symbolP->sy_resolving = 1;
	  resolved = resolve_expression (&expr);
	  symbolP->sy_resolving = 0;
	  if (!resolved)
	    return 0;

	  switch (expr.X_op)
	    {
	    case O_constant:
	    case O_register:
	      if (!symbol_equated_p (symbolP))
		break;
	      /* Fall thru.  */
	    case O_symbol:
	    case O_symbol_rva:
	      symbolP = expr.X_add_symbol;
	      break;
	    default:
	      return 0;
	    }
	}

      /* Never change a defined symbol.  */
      if (symbolP->bsym->section == undefined_section
	  || symbolP->bsym->section == expr_section)
	*symbolPP = symbolP;
      *valueP = expr.X_add_number;
      *segP = symbolP->bsym->section;
      *fragPP = symbolP->sy_frag;

      if (*segP == expr_section)
	switch (expr.X_op)
	  {
	  case O_constant: *segP = absolute_section; break;
	  case O_register: *segP = reg_section; break;
	  default: break;
	  }
    }

  return 1;
}