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
struct s5h1420_state {int dummy; } ;
typedef  int /*<<< orphan*/  fe_code_rate_t ;

/* Variables and functions */
 int /*<<< orphan*/  FEC_1_2 ; 
 int /*<<< orphan*/  FEC_2_3 ; 
 int /*<<< orphan*/  FEC_3_4 ; 
 int /*<<< orphan*/  FEC_5_6 ; 
 int /*<<< orphan*/  FEC_6_7 ; 
 int /*<<< orphan*/  FEC_7_8 ; 
 int /*<<< orphan*/  FEC_NONE ; 
 int s5h1420_readreg (struct s5h1420_state*,int) ; 

__attribute__((used)) static fe_code_rate_t s5h1420_getfec(struct s5h1420_state* state)
{
	switch(s5h1420_readreg(state, 0x32) & 0x07) {
	case 0:
		return FEC_1_2;

	case 1:
		return FEC_2_3;

	case 2:
		return FEC_3_4;

	case 3:
		return FEC_5_6;

	case 4:
		return FEC_6_7;

	case 5:
		return FEC_7_8;
	}

	return FEC_NONE;
}