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
struct specialix_board {unsigned short reg; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ SX_ADDR_REG ; 
 scalar_t__ SX_DATA_REG ; 
 unsigned char inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned short,scalar_t__) ; 

__attribute__((used)) static inline unsigned char sx_in(struct specialix_board *bp,
							unsigned short reg)
{
	bp->reg = reg | 0x80;
	outb(reg | 0x80, bp->base + SX_ADDR_REG);
	return inb(bp->base + SX_DATA_REG);
}