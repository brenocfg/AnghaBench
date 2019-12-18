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
typedef  int u32 ;
struct stv090x_state {int /*<<< orphan*/  fec; } ;

/* Variables and functions */
 int STV090x_GETFIELD_Px (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STV090x_PR12 ; 
 int /*<<< orphan*/  STV090x_PR23 ; 
 int /*<<< orphan*/  STV090x_PR34 ; 
 int /*<<< orphan*/  STV090x_PR56 ; 
 int /*<<< orphan*/  STV090x_PR67 ; 
 int /*<<< orphan*/  STV090x_PR78 ; 
 int /*<<< orphan*/  STV090x_PRERR ; 
 int STV090x_READ_DEMOD (struct stv090x_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VITCURPUN ; 
 int /*<<< orphan*/  VIT_CURPUN_FIELD ; 

__attribute__((used)) static int stv090x_get_viterbi(struct stv090x_state *state)
{
	u32 reg, rate;

	reg = STV090x_READ_DEMOD(state, VITCURPUN);
	rate = STV090x_GETFIELD_Px(reg, VIT_CURPUN_FIELD);

	switch (rate) {
	case 13:
		state->fec = STV090x_PR12;
		break;

	case 18:
		state->fec = STV090x_PR23;
		break;

	case 21:
		state->fec = STV090x_PR34;
		break;

	case 24:
		state->fec = STV090x_PR56;
		break;

	case 25:
		state->fec = STV090x_PR67;
		break;

	case 26:
		state->fec = STV090x_PR78;
		break;

	default:
		state->fec = STV090x_PRERR;
		break;
	}

	return 0;
}