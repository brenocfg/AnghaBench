#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ X_op; int X_add_number; } ;
typedef  TYPE_2__ expressionS ;
struct TYPE_7__ {TYPE_1__* operands; } ;
struct TYPE_5__ {int imm; int reg; int regisimm; } ;

/* Variables and functions */
 int FAIL ; 
 int /*<<< orphan*/  GE_OPT_PREFIX_BIG ; 
 int LITTLENUM_NUMBER_OF_BITS ; 
 scalar_t__ O_big ; 
 scalar_t__ O_constant ; 
 int SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int* generic_bignum ; 
 TYPE_4__ inst ; 
 int /*<<< orphan*/  my_get_expression (TYPE_2__*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
parse_big_immediate (char **str, int i)
{
  expressionS exp;
  char *ptr = *str;

  my_get_expression (&exp, &ptr, GE_OPT_PREFIX_BIG);

  if (exp.X_op == O_constant)
    {
      inst.operands[i].imm = exp.X_add_number & 0xffffffff;
      /* If we're on a 64-bit host, then a 64-bit number can be returned using
	 O_constant.  We have to be careful not to break compilation for
	 32-bit X_add_number, though.  */
      if ((exp.X_add_number & ~0xffffffffl) != 0)
	{
          /* X >> 32 is illegal if sizeof (exp.X_add_number) == 4.  */
	  inst.operands[i].reg = ((exp.X_add_number >> 16) >> 16) & 0xffffffff;
	  inst.operands[i].regisimm = 1;
	}
    }
  else if (exp.X_op == O_big
           && LITTLENUM_NUMBER_OF_BITS * exp.X_add_number > 32
           && LITTLENUM_NUMBER_OF_BITS * exp.X_add_number <= 64)
    {
      unsigned parts = 32 / LITTLENUM_NUMBER_OF_BITS, j, idx = 0;
      /* Bignums have their least significant bits in
         generic_bignum[0]. Make sure we put 32 bits in imm and
         32 bits in reg,  in a (hopefully) portable way.  */
      assert (parts != 0);
      inst.operands[i].imm = 0;
      for (j = 0; j < parts; j++, idx++)
        inst.operands[i].imm |= generic_bignum[idx]
                                << (LITTLENUM_NUMBER_OF_BITS * j);
      inst.operands[i].reg = 0;
      for (j = 0; j < parts; j++, idx++)
        inst.operands[i].reg |= generic_bignum[idx]
                                << (LITTLENUM_NUMBER_OF_BITS * j);
      inst.operands[i].regisimm = 1;
    }
  else
    return FAIL;
  
  *str = ptr;

  return SUCCESS;
}