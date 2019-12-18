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
struct TYPE_8__ {scalar_t__ X_op; scalar_t__ X_add_number; } ;
typedef  TYPE_1__ expressionS ;
typedef  enum bfd_reloc_code_real { ____Placeholder_bfd_reloc_code_real } bfd_reloc_code_real ;
struct TYPE_9__ {int fr_literal; } ;

/* Variables and functions */
 int BFD_RELOC_SPU_PPU32 ; 
 int BFD_RELOC_SPU_PPU64 ; 
 scalar_t__ O_constant ; 
 scalar_t__ O_symbol ; 
 int /*<<< orphan*/  deferred_expression (TYPE_1__*) ; 
 int /*<<< orphan*/  demand_empty_rest_of_line () ; 
 int /*<<< orphan*/  emit_expr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  expression (TYPE_1__*) ; 
 int /*<<< orphan*/  fix_new_exp (TYPE_2__*,char*,int,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 char* frag_more (int) ; 
 TYPE_2__* frag_now ; 
 char* input_line_pointer ; 
 scalar_t__ is_it_end_of_statement () ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 

__attribute__((used)) static void
spu_cons (int nbytes)
{
  expressionS exp;

  if (is_it_end_of_statement ())
    {
      demand_empty_rest_of_line ();
      return;
    }

  do
    {
      deferred_expression (&exp);
      if ((exp.X_op == O_symbol
	   || exp.X_op == O_constant)
	  && strncasecmp (input_line_pointer, "@ppu", 4) == 0)
	{
	  char *p = frag_more (nbytes);
	  enum bfd_reloc_code_real reloc;

	  /* Check for identifier@suffix+constant.  */
	  input_line_pointer += 4;
	  if (*input_line_pointer == '-' || *input_line_pointer == '+')
	    {
	      expressionS new_exp;

	      expression (&new_exp);
	      if (new_exp.X_op == O_constant)
		exp.X_add_number += new_exp.X_add_number;
	    }

	  reloc = nbytes == 4 ? BFD_RELOC_SPU_PPU32 : BFD_RELOC_SPU_PPU64;
	  fix_new_exp (frag_now, p - frag_now->fr_literal, nbytes,
		       &exp, 0, reloc);
	}
      else
	emit_expr (&exp, nbytes);
    }
  while (*input_line_pointer++ == ',');

  /* Put terminator back into stream.  */
  input_line_pointer--;
  demand_empty_rest_of_line ();
}