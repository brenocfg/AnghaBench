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
struct tda10086_state {int dummy; } ;

/* Variables and functions */
 int tda10086_read_byte (struct tda10086_state*,int) ; 
 int tda10086_write_byte (struct tda10086_state*,int,int) ; 

__attribute__((used)) static int tda10086_write_mask(struct tda10086_state *state, int reg, int mask, int data)
{
	int val;

	/* read a byte and check */
	val = tda10086_read_byte(state, reg);
	if (val < 0)
		return val;

	/* mask if off */
	val = val & ~mask;
	val |= data & 0xff;

	/* write it out again */
	return tda10086_write_byte(state, reg, val);
}