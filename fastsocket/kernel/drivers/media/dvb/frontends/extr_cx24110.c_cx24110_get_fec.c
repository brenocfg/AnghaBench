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
struct cx24110_state {int dummy; } ;
typedef  scalar_t__ fe_code_rate_t ;

/* Variables and functions */
 scalar_t__ FEC_1_2 ; 
 scalar_t__ FEC_NONE ; 
 int cx24110_readreg (struct cx24110_state*,int) ; 

__attribute__((used)) static fe_code_rate_t cx24110_get_fec (struct cx24110_state* state)
{
	int i;

	i=cx24110_readreg(state,0x22)&0x0f;
	if(!(i&0x08)) {
		return FEC_1_2 + i - 1;
	} else {
/* fixme (low): a special code rate has been selected. In theory, we need to
   return a denominator value, a numerator value, and a pair of puncture
   maps to correctly describe this mode. But this should never happen in
   practice, because it cannot be set by cx24110_get_fec. */
	   return FEC_NONE;
	}
}