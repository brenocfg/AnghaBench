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
struct ves1x93_state {int dummy; } ;
typedef  scalar_t__ fe_code_rate_t ;

/* Variables and functions */
 scalar_t__ FEC_1_2 ; 
 int ves1x93_readreg (struct ves1x93_state*,int) ; 

__attribute__((used)) static fe_code_rate_t ves1x93_get_fec (struct ves1x93_state* state)
{
	return FEC_1_2 + ((ves1x93_readreg (state, 0x0d) >> 4) & 0x7);
}