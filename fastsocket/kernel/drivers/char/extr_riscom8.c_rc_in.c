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
struct riscom_board {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ RC_TO_ISA (unsigned short) ; 
 unsigned char inb (scalar_t__) ; 

__attribute__((used)) static inline unsigned char rc_in(struct riscom_board const *bp,
							unsigned short reg)
{
	return inb(bp->base + RC_TO_ISA(reg));
}