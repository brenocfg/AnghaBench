#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  expressionS ;
struct TYPE_3__ {int fr_literal; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_RELOC_MIPS_JALR ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ HAVE_NEWABI ; 
 int /*<<< orphan*/  PIC_CALL_REG ; 
 int /*<<< orphan*/  RA ; 
 int /*<<< orphan*/  fix_new_exp (TYPE_1__*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frag_grow (int) ; 
 char* frag_more (int /*<<< orphan*/ ) ; 
 TYPE_1__* frag_now ; 
 int /*<<< orphan*/  macro_build (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
macro_build_jalr (expressionS *ep)
{
  char *f = NULL;

  if (HAVE_NEWABI)
    {
      frag_grow (8);
      f = frag_more (0);
    }
  macro_build (NULL, "jalr", "d,s", RA, PIC_CALL_REG);
  if (HAVE_NEWABI)
    fix_new_exp (frag_now, f - frag_now->fr_literal,
		 4, ep, FALSE, BFD_RELOC_MIPS_JALR);
}