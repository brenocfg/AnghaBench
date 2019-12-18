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
struct stv0297_state {int dummy; } ;
typedef  long s32 ;

/* Variables and functions */
 long STV0297_CLOCK_KHZ ; 
 int /*<<< orphan*/  stv0297_writereg (struct stv0297_state*,int,long) ; 
 int /*<<< orphan*/  stv0297_writereg_mask (struct stv0297_state*,int,int,int) ; 

__attribute__((used)) static void stv0297_set_initialdemodfreq(struct stv0297_state *state, long freq)
{
	s32 tmp;

	if (freq > 10000)
		freq -= STV0297_CLOCK_KHZ;

	tmp = (STV0297_CLOCK_KHZ * 1000) / (1 << 16);
	tmp = (freq * 1000) / tmp;
	if (tmp > 0xffff)
		tmp = 0xffff;

	stv0297_writereg_mask(state, 0x25, 0x80, 0x80);
	stv0297_writereg(state, 0x21, tmp >> 8);
	stv0297_writereg(state, 0x20, tmp);
}