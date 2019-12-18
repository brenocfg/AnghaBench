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
typedef  int fe_spectral_inversion_t ;

/* Variables and functions */
 int EINVAL ; 
#define  INVERSION_AUTO 130 
#define  INVERSION_OFF 129 
#define  INVERSION_ON 128 
 int cx24110_readreg (struct cx24110_state*,int) ; 
 int /*<<< orphan*/  cx24110_writereg (struct cx24110_state*,int,int) ; 

__attribute__((used)) static int cx24110_set_inversion (struct cx24110_state* state, fe_spectral_inversion_t inversion)
{
/* fixme (low): error handling */

	switch (inversion) {
	case INVERSION_OFF:
		cx24110_writereg(state,0x37,cx24110_readreg(state,0x37)|0x1);
		/* AcqSpectrInvDis on. No idea why someone should want this */
		cx24110_writereg(state,0x5,cx24110_readreg(state,0x5)&0xf7);
		/* Initial value 0 at start of acq */
		cx24110_writereg(state,0x22,cx24110_readreg(state,0x22)&0xef);
		/* current value 0 */
		/* The cx24110 manual tells us this reg is read-only.
		   But what the heck... set it ayways */
		break;
	case INVERSION_ON:
		cx24110_writereg(state,0x37,cx24110_readreg(state,0x37)|0x1);
		/* AcqSpectrInvDis on. No idea why someone should want this */
		cx24110_writereg(state,0x5,cx24110_readreg(state,0x5)|0x08);
		/* Initial value 1 at start of acq */
		cx24110_writereg(state,0x22,cx24110_readreg(state,0x22)|0x10);
		/* current value 1 */
		break;
	case INVERSION_AUTO:
		cx24110_writereg(state,0x37,cx24110_readreg(state,0x37)&0xfe);
		/* AcqSpectrInvDis off. Leave initial & current states as is */
		break;
	default:
		return -EINVAL;
	}

	return 0;
}