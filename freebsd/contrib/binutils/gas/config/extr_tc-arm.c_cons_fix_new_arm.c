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
typedef  int /*<<< orphan*/  bfd_reloc_code_real_type ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_RELOC_16 ; 
 int /*<<< orphan*/  BFD_RELOC_32 ; 
 int /*<<< orphan*/  BFD_RELOC_32_SECREL ; 
 int /*<<< orphan*/  BFD_RELOC_64 ; 
 int /*<<< orphan*/  BFD_RELOC_8 ; 
 scalar_t__ O_secrel ; 
 scalar_t__ O_symbol ; 
 int /*<<< orphan*/  fix_new_exp (int /*<<< orphan*/ *,int,int,TYPE_1__*,int,int /*<<< orphan*/ ) ; 

void
cons_fix_new_arm (fragS *	frag,
		  int		where,
		  int		size,
		  expressionS * exp)
{
  bfd_reloc_code_real_type type;
  int pcrel = 0;

  /* Pick a reloc.
     FIXME: @@ Should look at CPU word size.  */
  switch (size)
    {
    case 1:
      type = BFD_RELOC_8;
      break;
    case 2:
      type = BFD_RELOC_16;
      break;
    case 4:
    default:
      type = BFD_RELOC_32;
      break;
    case 8:
      type = BFD_RELOC_64;
      break;
    }

#ifdef TE_PE
  if (exp->X_op == O_secrel)
  {
    exp->X_op = O_symbol;
    type = BFD_RELOC_32_SECREL;
  }
#endif

  fix_new_exp (frag, where, (int) size, exp, pcrel, type);
}