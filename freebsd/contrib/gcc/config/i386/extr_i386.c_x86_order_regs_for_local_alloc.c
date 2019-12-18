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

/* Variables and functions */
 int FIRST_MMX_REG ; 
 int FIRST_PSEUDO_REGISTER ; 
 int FIRST_REX_SSE_REG ; 
 int FIRST_SSE_REG ; 
 int FIRST_STACK_REG ; 
 scalar_t__ GENERAL_REGNO_P (int) ; 
 int LAST_MMX_REG ; 
 int LAST_REX_SSE_REG ; 
 int LAST_SSE_REG ; 
 int LAST_STACK_REG ; 
 scalar_t__ TARGET_SSE_MATH ; 
 scalar_t__* call_used_regs ; 
 int* reg_alloc_order ; 

void
x86_order_regs_for_local_alloc (void)
{
   int pos = 0;
   int i;

   /* First allocate the local general purpose registers.  */
   for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
     if (GENERAL_REGNO_P (i) && call_used_regs[i])
	reg_alloc_order [pos++] = i;

   /* Global general purpose registers.  */
   for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
     if (GENERAL_REGNO_P (i) && !call_used_regs[i])
	reg_alloc_order [pos++] = i;

   /* x87 registers come first in case we are doing FP math
      using them.  */
   if (!TARGET_SSE_MATH)
     for (i = FIRST_STACK_REG; i <= LAST_STACK_REG; i++)
       reg_alloc_order [pos++] = i;

   /* SSE registers.  */
   for (i = FIRST_SSE_REG; i <= LAST_SSE_REG; i++)
     reg_alloc_order [pos++] = i;
   for (i = FIRST_REX_SSE_REG; i <= LAST_REX_SSE_REG; i++)
     reg_alloc_order [pos++] = i;

   /* x87 registers.  */
   if (TARGET_SSE_MATH)
     for (i = FIRST_STACK_REG; i <= LAST_STACK_REG; i++)
       reg_alloc_order [pos++] = i;

   for (i = FIRST_MMX_REG; i <= LAST_MMX_REG; i++)
     reg_alloc_order [pos++] = i;

   /* Initialize the rest of array as we do not allocate some registers
      at all.  */
   while (pos < FIRST_PSEUDO_REGISTER)
     reg_alloc_order [pos++] = 0;
}