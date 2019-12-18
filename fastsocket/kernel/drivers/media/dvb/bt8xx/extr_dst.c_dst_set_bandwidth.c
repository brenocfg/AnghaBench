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
struct dst_state {int bandwidth; scalar_t__ dst_type; int dst_hw_cap; int* tx_tuna; } ;
typedef  int fe_bandwidth_t ;

/* Variables and functions */
#define  BANDWIDTH_6_MHZ 130 
#define  BANDWIDTH_7_MHZ 129 
#define  BANDWIDTH_8_MHZ 128 
 int DST_TYPE_HAS_CA ; 
 scalar_t__ DST_TYPE_IS_TERR ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 

__attribute__((used)) static int dst_set_bandwidth(struct dst_state *state, fe_bandwidth_t bandwidth)
{
	state->bandwidth = bandwidth;

	if (state->dst_type != DST_TYPE_IS_TERR)
		return -EOPNOTSUPP;

	switch (bandwidth) {
	case BANDWIDTH_6_MHZ:
		if (state->dst_hw_cap & DST_TYPE_HAS_CA)
			state->tx_tuna[7] = 0x06;
		else {
			state->tx_tuna[6] = 0x06;
			state->tx_tuna[7] = 0x00;
		}
		break;
	case BANDWIDTH_7_MHZ:
		if (state->dst_hw_cap & DST_TYPE_HAS_CA)
			state->tx_tuna[7] = 0x07;
		else {
			state->tx_tuna[6] = 0x07;
			state->tx_tuna[7] = 0x00;
		}
		break;
	case BANDWIDTH_8_MHZ:
		if (state->dst_hw_cap & DST_TYPE_HAS_CA)
			state->tx_tuna[7] = 0x08;
		else {
			state->tx_tuna[6] = 0x08;
			state->tx_tuna[7] = 0x00;
		}
		break;
	default:
		return -EINVAL;
	}

	return 0;
}