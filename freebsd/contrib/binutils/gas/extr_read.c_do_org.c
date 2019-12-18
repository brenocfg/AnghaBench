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
typedef  scalar_t__ segT ;
typedef  int /*<<< orphan*/  relax_substateT ;
typedef  int offsetT ;
struct TYPE_4__ {scalar_t__ X_op; int X_add_number; int /*<<< orphan*/ * X_add_symbol; } ;
typedef  TYPE_1__ expressionS ;

/* Variables and functions */
 int OCTETS_PER_BYTE ; 
 scalar_t__ O_constant ; 
 scalar_t__ O_symbol ; 
 int /*<<< orphan*/  _ (char*) ; 
 int abs_section_offset ; 
 scalar_t__ absolute_section ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ) ; 
 char* frag_var (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/ * make_expr_symbol (TYPE_1__*) ; 
 scalar_t__ now_seg ; 
 int /*<<< orphan*/  rs_org ; 
 int /*<<< orphan*/  segment_name (scalar_t__) ; 

__attribute__((used)) static void
do_org (segT segment, expressionS *exp, int fill)
{
  if (segment != now_seg && segment != absolute_section)
    as_bad (_("invalid segment \"%s\""), segment_name (segment));

  if (now_seg == absolute_section)
    {
      if (fill != 0)
	as_warn (_("ignoring fill value in absolute section"));
      if (exp->X_op != O_constant)
	{
	  as_bad (_("only constant offsets supported in absolute section"));
	  exp->X_add_number = 0;
	}
      abs_section_offset = exp->X_add_number;
    }
  else
    {
      char *p;
      symbolS *sym = exp->X_add_symbol;
      offsetT off = exp->X_add_number * OCTETS_PER_BYTE;

      if (exp->X_op != O_constant && exp->X_op != O_symbol)
	{
	  /* Handle complex expressions.  */
	  sym = make_expr_symbol (exp);
	  off = 0;
	}

      p = frag_var (rs_org, 1, 1, (relax_substateT) 0, sym, off, (char *) 0);
      *p = fill;
    }
}