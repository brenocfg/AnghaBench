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
typedef  int /*<<< orphan*/  fragS ;
struct TYPE_4__ {scalar_t__ X_op; } ;
typedef  TYPE_1__ expressionS ;
typedef  enum bfd_reloc_code_real { ____Placeholder_bfd_reloc_code_real } bfd_reloc_code_real ;

/* Variables and functions */
 int BFD_RELOC_32_SECREL ; 
 int /*<<< orphan*/  NO_RELOC ; 
 scalar_t__ O_secrel ; 
 scalar_t__ O_symbol ; 
 int /*<<< orphan*/  cons_sign ; 
 int /*<<< orphan*/  fix_new_exp (int /*<<< orphan*/ *,unsigned int,unsigned int,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  got_reloc ; 
 int reloc (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
x86_cons_fix_new (fragS *frag, unsigned int off, unsigned int len,
		  expressionS *exp)
{
  enum bfd_reloc_code_real r = reloc (len, 0, cons_sign, got_reloc);

  got_reloc = NO_RELOC;

#ifdef TE_PE
  if (exp->X_op == O_secrel)
    {
      exp->X_op = O_symbol;
      r = BFD_RELOC_32_SECREL;
    }
#endif

  fix_new_exp (frag, off, len, exp, 0, r);
}