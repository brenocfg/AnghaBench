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
typedef  int u8 ;
struct tda10023_state {int dummy; } ;

/* Variables and functions */
 int tda10023_readreg (struct tda10023_state*,int) ; 
 int tda10023_writereg (struct tda10023_state*,int,int) ; 

__attribute__((used)) static int tda10023_writebit (struct tda10023_state* state, u8 reg, u8 mask,u8 data)
{
	if (mask==0xff)
		return tda10023_writereg(state, reg, data);
	else {
		u8 val;
		val=tda10023_readreg(state,reg);
		val&=~mask;
		val|=(data&mask);
		return tda10023_writereg(state, reg, val);
	}
}