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
struct stv0297_state {int dummy; } ;
typedef  int fe_spectral_inversion_t ;

/* Variables and functions */
 int EINVAL ; 
#define  INVERSION_OFF 129 
#define  INVERSION_ON 128 
 int /*<<< orphan*/  stv0297_writereg_mask (struct stv0297_state*,int,int,int) ; 

__attribute__((used)) static int stv0297_set_inversion(struct stv0297_state *state, fe_spectral_inversion_t inversion)
{
	int val = 0;

	switch (inversion) {
	case INVERSION_OFF:
		val = 0;
		break;

	case INVERSION_ON:
		val = 1;
		break;

	default:
		return -EINVAL;
	}

	stv0297_writereg_mask(state, 0x83, 0x08, val << 3);

	return 0;
}