#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  fragS ;
typedef  int /*<<< orphan*/  expressionS ;

/* Variables and functions */
 int BFD_RELOC_CR16_NUM16 ; 
 int BFD_RELOC_CR16_NUM32 ; 
 int BFD_RELOC_CR16_NUM32a ; 
 int BFD_RELOC_CR16_NUM8 ; 
 int BFD_RELOC_NONE ; 
 int /*<<< orphan*/  code_label ; 
 int /*<<< orphan*/  fix_new_exp (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void
cr16_cons_fix_new (fragS *frag, int offset, int len, expressionS *exp)
{
  int rtype;
  switch (len)
    {
    default: rtype = BFD_RELOC_NONE; break;
    case 1: rtype = BFD_RELOC_CR16_NUM8 ; break;
    case 2: rtype = BFD_RELOC_CR16_NUM16; break;
    case 4:
      if (code_label)
	{
	  rtype = BFD_RELOC_CR16_NUM32a;
	  code_label = 0;
	}
      else
	rtype = BFD_RELOC_CR16_NUM32;
      break;
    }

  fix_new_exp (frag, offset, len, exp, 0, rtype);
}