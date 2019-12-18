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
struct ves1x93_state {int* init_1x93_tab; } ;
typedef  int fe_spectral_inversion_t ;

/* Variables and functions */
 int EINVAL ; 
#define  INVERSION_AUTO 130 
#define  INVERSION_OFF 129 
#define  INVERSION_ON 128 
 int ves1x93_writereg (struct ves1x93_state*,int,int) ; 

__attribute__((used)) static int ves1x93_set_inversion (struct ves1x93_state* state, fe_spectral_inversion_t inversion)
{
	u8 val;

	/*
	 * inversion on/off are interchanged because i and q seem to
	 * be swapped on the hardware
	 */

	switch (inversion) {
	case INVERSION_OFF:
		val = 0xc0;
		break;
	case INVERSION_ON:
		val = 0x80;
		break;
	case INVERSION_AUTO:
		val = 0x00;
		break;
	default:
		return -EINVAL;
	}

	return ves1x93_writereg (state, 0x0c, (state->init_1x93_tab[0x0c] & 0x3f) | val);
}