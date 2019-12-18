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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct stv0297_state {int dummy; } ;

/* Variables and functions */
 int STV0297_CLOCK_KHZ ; 
 int stv0297_readreg (struct stv0297_state*,int) ; 

__attribute__((used)) static u32 stv0297_get_symbolrate(struct stv0297_state *state)
{
	u64 tmp;

	tmp = stv0297_readreg(state, 0x55);
	tmp |= stv0297_readreg(state, 0x56) << 8;
	tmp |= stv0297_readreg(state, 0x57) << 16;
	tmp |= stv0297_readreg(state, 0x58) << 24;

	tmp *= STV0297_CLOCK_KHZ;
	tmp >>= 32;

	return (u32) tmp;
}