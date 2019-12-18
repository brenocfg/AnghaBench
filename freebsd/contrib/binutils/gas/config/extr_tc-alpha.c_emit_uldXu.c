#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  X_add_number; } ;
typedef  TYPE_1__ expressionS ;

/* Variables and functions */
 int /*<<< orphan*/  AXP_REG_AT ; 
 int /*<<< orphan*/  AXP_REG_T10 ; 
 int /*<<< orphan*/  AXP_REG_T9 ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ alpha_noat_on ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assemble_tokens (char*,TYPE_1__*,int,int) ; 
 char** extXh_op ; 
 char** extXl_op ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__ const*,int) ; 
 int /*<<< orphan*/  set_tok_const (TYPE_1__,int) ; 
 int /*<<< orphan*/  set_tok_preg (TYPE_1__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tok_reg (TYPE_1__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
emit_uldXu (const expressionS *tok,
	    int ntok,
	    const void * vlgsize)
{
  long lgsize = (long) vlgsize;
  expressionS newtok[3];

  if (alpha_noat_on)
    as_bad (_("macro requires $at register while noat in effect"));

  /* Emit "lda $at, exp".  */
  memcpy (newtok, tok, sizeof (expressionS) * ntok);
  newtok[0].X_add_number = AXP_REG_AT;
  assemble_tokens ("lda", newtok, ntok, 1);

  /* Emit "ldq_u $t9, 0($at)".  */
  set_tok_reg (newtok[0], AXP_REG_T9);
  set_tok_const (newtok[1], 0);
  set_tok_preg (newtok[2], AXP_REG_AT);
  assemble_tokens ("ldq_u", newtok, 3, 1);

  /* Emit "ldq_u $t10, size-1($at)".  */
  set_tok_reg (newtok[0], AXP_REG_T10);
  set_tok_const (newtok[1], (1 << lgsize) - 1);
  assemble_tokens ("ldq_u", newtok, 3, 1);

  /* Emit "extXl $t9, $at, $t9".  */
  set_tok_reg (newtok[0], AXP_REG_T9);
  set_tok_reg (newtok[1], AXP_REG_AT);
  set_tok_reg (newtok[2], AXP_REG_T9);
  assemble_tokens (extXl_op[lgsize], newtok, 3, 1);

  /* Emit "extXh $t10, $at, $t10".  */
  set_tok_reg (newtok[0], AXP_REG_T10);
  set_tok_reg (newtok[2], AXP_REG_T10);
  assemble_tokens (extXh_op[lgsize], newtok, 3, 1);

  /* Emit "or $t9, $t10, targ".  */
  set_tok_reg (newtok[0], AXP_REG_T9);
  set_tok_reg (newtok[1], AXP_REG_T10);
  newtok[2] = tok[0];
  assemble_tokens ("or", newtok, 3, 1);
}