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
typedef  int uint32_t ;
typedef  int tmrHw_ID_t ;
typedef  int tmrHw_CAPABILITY_e ;

/* Variables and functions */
#define  tmrHw_CAPABILITY_CLOCK 129 
#define  tmrHw_CAPABILITY_RESOLUTION 128 
 int tmrHw_HIGH_RESOLUTION_CLOCK ; 
 int tmrHw_LOW_RESOLUTION_CLOCK ; 

uint32_t tmrHw_getTimerCapability(tmrHw_ID_t timerId,	/*  [ IN ] Timer Id */
				  tmrHw_CAPABILITY_e capability	/*  [ IN ] Timer capability */
) {
	switch (capability) {
	case tmrHw_CAPABILITY_CLOCK:
		return (timerId <=
			1) ? tmrHw_LOW_RESOLUTION_CLOCK :
		    tmrHw_HIGH_RESOLUTION_CLOCK;
	case tmrHw_CAPABILITY_RESOLUTION:
		return 32;
	default:
		return 0;
	}
	return 0;
}