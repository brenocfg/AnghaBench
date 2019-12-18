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
struct dst_state {int voltage; int* tx_tuna; } ;

/* Variables and functions */
 int /*<<< orphan*/  DST_INFO ; 
#define  SEC_VOLTAGE_13 130 
#define  SEC_VOLTAGE_18 129 
#define  SEC_VOLTAGE_OFF 128 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int dst_set_polarization(struct dst_state *state)
{
	switch (state->voltage) {
	case SEC_VOLTAGE_13:	/*	Vertical	*/
		dprintk(verbose, DST_INFO, 1, "Polarization=[Vertical]");
		state->tx_tuna[8] &= ~0x40;
		break;
	case SEC_VOLTAGE_18:	/*	Horizontal	*/
		dprintk(verbose, DST_INFO, 1, "Polarization=[Horizontal]");
		state->tx_tuna[8] |= 0x40;
		break;
	case SEC_VOLTAGE_OFF:
		break;
	}

	return 0;
}