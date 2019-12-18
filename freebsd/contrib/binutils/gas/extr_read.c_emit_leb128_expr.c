#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ valueT ;
typedef  scalar_t__ operatorT ;
struct TYPE_6__ {scalar_t__ X_op; scalar_t__ X_add_number; int /*<<< orphan*/  X_unsigned; } ;
typedef  TYPE_1__ expressionS ;

/* Variables and functions */
 scalar_t__ O_absent ; 
 scalar_t__ O_big ; 
 scalar_t__ O_constant ; 
 scalar_t__ O_illegal ; 
 scalar_t__ O_register ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ) ; 
 scalar_t__ check_eh_frame (TYPE_1__*,unsigned int*) ; 
 int /*<<< orphan*/  convert_to_bignum (TYPE_1__*) ; 
 char* frag_more (int) ; 
 int /*<<< orphan*/  frag_var (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  generic_bignum ; 
 int /*<<< orphan*/  make_expr_symbol (TYPE_1__*) ; 
 int /*<<< orphan*/  md_cons_align (int) ; 
 int output_big_leb128 (char*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  output_leb128 (char*,scalar_t__,int) ; 
 int /*<<< orphan*/  rs_leb128 ; 
 int sizeof_leb128 (scalar_t__,int) ; 
 int /*<<< orphan*/  sizeof_uleb128 (scalar_t__) ; 

__attribute__((used)) static void
emit_leb128_expr (expressionS *exp, int sign)
{
  operatorT op = exp->X_op;
  unsigned int nbytes;

  if (op == O_absent || op == O_illegal)
    {
      as_warn (_("zero assumed for missing expression"));
      exp->X_add_number = 0;
      op = O_constant;
    }
  else if (op == O_big && exp->X_add_number <= 0)
    {
      as_bad (_("floating point number invalid"));
      exp->X_add_number = 0;
      op = O_constant;
    }
  else if (op == O_register)
    {
      as_warn (_("register value used as expression"));
      op = O_constant;
    }
  else if (op == O_constant
	   && sign
	   && (exp->X_add_number < 0) != !exp->X_unsigned)
    {
      /* We're outputting a signed leb128 and the sign of X_add_number
	 doesn't reflect the sign of the original value.  Convert EXP
	 to a correctly-extended bignum instead.  */
      convert_to_bignum (exp);
      op = O_big;
    }

  /* Let check_eh_frame know that data is being emitted.  nbytes == -1 is
     a signal that this is leb128 data.  It shouldn't optimize this away.  */
  nbytes = (unsigned int) -1;
  if (check_eh_frame (exp, &nbytes))
    abort ();

  /* Let the backend know that subsequent data may be byte aligned.  */
#ifdef md_cons_align
  md_cons_align (1);
#endif

  if (op == O_constant)
    {
      /* If we've got a constant, emit the thing directly right now.  */

      valueT value = exp->X_add_number;
      int size;
      char *p;

      size = sizeof_leb128 (value, sign);
      p = frag_more (size);
      output_leb128 (p, value, sign);
    }
  else if (op == O_big)
    {
      /* O_big is a different sort of constant.  */

      int size;
      char *p;

      size = output_big_leb128 (NULL, generic_bignum, exp->X_add_number, sign);
      p = frag_more (size);
      output_big_leb128 (p, generic_bignum, exp->X_add_number, sign);
    }
  else
    {
      /* Otherwise, we have to create a variable sized fragment and
	 resolve things later.  */

      frag_var (rs_leb128, sizeof_uleb128 (~(valueT) 0), 0, sign,
		make_expr_symbol (exp), 0, (char *) NULL);
    }
}