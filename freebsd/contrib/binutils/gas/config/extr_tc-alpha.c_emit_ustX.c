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
 int /*<<< orphan*/  AXP_REG_T11 ; 
 int /*<<< orphan*/  AXP_REG_T12 ; 
 int /*<<< orphan*/  AXP_REG_T9 ; 
 int /*<<< orphan*/  assemble_tokens (char*,TYPE_1__*,int,int) ; 
 char** insXh_op ; 
 char** insXl_op ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__ const*,int) ; 
 char** mskXh_op ; 
 char** mskXl_op ; 
 int /*<<< orphan*/  set_tok_const (TYPE_1__,int) ; 
 int /*<<< orphan*/  set_tok_preg (TYPE_1__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tok_reg (TYPE_1__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
emit_ustX (const expressionS *tok,
	   int ntok,
	   const void * vlgsize)
{
  int lgsize = (int) (long) vlgsize;
  expressionS newtok[3];

  /* Emit "lda $at, exp".  */
  memcpy (newtok, tok, sizeof (expressionS) * ntok);
  newtok[0].X_add_number = AXP_REG_AT;
  assemble_tokens ("lda", newtok, ntok, 1);

  /* Emit "ldq_u $9, 0($at)".  */
  set_tok_reg (newtok[0], AXP_REG_T9);
  set_tok_const (newtok[1], 0);
  set_tok_preg (newtok[2], AXP_REG_AT);
  assemble_tokens ("ldq_u", newtok, 3, 1);

  /* Emit "ldq_u $10, size-1($at)".  */
  set_tok_reg (newtok[0], AXP_REG_T10);
  set_tok_const (newtok[1], (1 << lgsize) - 1);
  assemble_tokens ("ldq_u", newtok, 3, 1);

  /* Emit "insXl src, $at, $t11".  */
  newtok[0] = tok[0];
  set_tok_reg (newtok[1], AXP_REG_AT);
  set_tok_reg (newtok[2], AXP_REG_T11);
  assemble_tokens (insXl_op[lgsize], newtok, 3, 1);

  /* Emit "insXh src, $at, $t12".  */
  set_tok_reg (newtok[2], AXP_REG_T12);
  assemble_tokens (insXh_op[lgsize], newtok, 3, 1);

  /* Emit "mskXl $t9, $at, $t9".  */
  set_tok_reg (newtok[0], AXP_REG_T9);
  newtok[2] = newtok[0];
  assemble_tokens (mskXl_op[lgsize], newtok, 3, 1);

  /* Emit "mskXh $t10, $at, $t10".  */
  set_tok_reg (newtok[0], AXP_REG_T10);
  newtok[2] = newtok[0];
  assemble_tokens (mskXh_op[lgsize], newtok, 3, 1);

  /* Emit "or $t9, $t11, $t9".  */
  set_tok_reg (newtok[0], AXP_REG_T9);
  set_tok_reg (newtok[1], AXP_REG_T11);
  newtok[2] = newtok[0];
  assemble_tokens ("or", newtok, 3, 1);

  /* Emit "or $t10, $t12, $t10".  */
  set_tok_reg (newtok[0], AXP_REG_T10);
  set_tok_reg (newtok[1], AXP_REG_T12);
  newtok[2] = newtok[0];
  assemble_tokens ("or", newtok, 3, 1);

  /* Emit "stq_u $t10, size-1($at)".  */
  set_tok_reg (newtok[0], AXP_REG_T10);
  set_tok_const (newtok[1], (1 << lgsize) - 1);
  set_tok_preg (newtok[2], AXP_REG_AT);
  assemble_tokens ("stq_u", newtok, 3, 1);

  /* Emit "stq_u $t9, 0($at)".  */
  set_tok_reg (newtok[0], AXP_REG_T9);
  set_tok_const (newtok[1], 0);
  assemble_tokens ("stq_u", newtok, 3, 1);
}