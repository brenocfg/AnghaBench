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

/* Variables and functions */
#define  EEE_MODE_NVRAM_AGGRESSIVE_TIME 130 
#define  EEE_MODE_NVRAM_BALANCED_TIME 129 
#define  EEE_MODE_NVRAM_LATENCY_TIME 128 
 int PORT_FEAT_CFG_EEE_POWER_MODE_AGGRESSIVE ; 
 int PORT_FEAT_CFG_EEE_POWER_MODE_BALANCED ; 
 int PORT_FEAT_CFG_EEE_POWER_MODE_DISABLED ; 
 int PORT_FEAT_CFG_EEE_POWER_MODE_LOW_LATENCY ; 

__attribute__((used)) static int bnx2x_eee_time_to_nvram(u32 idle_timer, u32 *nvram_mode)
{
	switch (idle_timer) {
	case EEE_MODE_NVRAM_BALANCED_TIME:
		*nvram_mode = PORT_FEAT_CFG_EEE_POWER_MODE_BALANCED;
		break;
	case EEE_MODE_NVRAM_AGGRESSIVE_TIME:
		*nvram_mode = PORT_FEAT_CFG_EEE_POWER_MODE_AGGRESSIVE;
		break;
	case EEE_MODE_NVRAM_LATENCY_TIME:
		*nvram_mode = PORT_FEAT_CFG_EEE_POWER_MODE_LOW_LATENCY;
		break;
	default:
		*nvram_mode = PORT_FEAT_CFG_EEE_POWER_MODE_DISABLED;
		break;
	}

	return 0;
}