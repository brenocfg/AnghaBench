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
typedef  enum avmcardtype { ____Placeholder_avmcardtype } avmcardtype ;

/* Variables and functions */
 int /*<<< orphan*/  B1_INSTAT ; 
 int /*<<< orphan*/  B1_RESET ; 
 int /*<<< orphan*/  T1_IRQMASTER ; 
#define  avm_b1isa 134 
#define  avm_b1pci 133 
#define  avm_c4 132 
#define  avm_m1 131 
#define  avm_m2 130 
#define  avm_t1isa 129 
#define  avm_t1pci 128 
 int* b1_irq_table ; 
 int /*<<< orphan*/  b1outp (unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t1outp (unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void b1_setinterrupt(unsigned int base, unsigned irq,
				   enum avmcardtype cardtype)
{
	switch (cardtype) {
	   case avm_t1isa:
              t1outp(base, B1_INSTAT, 0x00);
              t1outp(base, B1_INSTAT, 0x02);
	      t1outp(base, T1_IRQMASTER, 0x08);
	      break;
	   case avm_b1isa:
	      b1outp(base, B1_INSTAT, 0x00);
	      b1outp(base, B1_RESET, b1_irq_table[irq]);
	      b1outp(base, B1_INSTAT, 0x02);
	      break;
	   default:
	   case avm_m1:
	   case avm_m2:
	   case avm_b1pci:
	      b1outp(base, B1_INSTAT, 0x00);
	      b1outp(base, B1_RESET, 0xf0);
	      b1outp(base, B1_INSTAT, 0x02);
	      break;
	   case avm_c4:
	   case avm_t1pci:
	      b1outp(base, B1_RESET, 0xf0);
	      break;
	 }
}