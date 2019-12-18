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
 unsigned char EOC ; 
 scalar_t__ PAR_DATA ; 
 unsigned char WrAddr ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 

__attribute__((used)) static inline void
write_reg(short port, unsigned char reg, unsigned char value)
{
    unsigned char outval;
    outb(EOC | reg, port + PAR_DATA);
    outval = WrAddr | reg;
    outb(outval, port + PAR_DATA);
    outb(outval, port + PAR_DATA);	/* Double write for PS/2. */

    outval &= 0xf0;
    outval |= value;
    outb(outval, port + PAR_DATA);
    outval &= 0x1f;
    outb(outval, port + PAR_DATA);
    outb(outval, port + PAR_DATA);

    outb(EOC | outval, port + PAR_DATA);
}