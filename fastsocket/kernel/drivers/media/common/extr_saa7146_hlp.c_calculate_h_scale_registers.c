#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct saa7146_dev {int dummy; } ;
struct TYPE_2__ {int hps_coeff; int weight_sum; } ;

/* Variables and functions */
 int EINVAL ; 
 int MASK_29 ; 
 int MASK_B2 ; 
 int MASK_W0 ; 
 int MASK_W1 ; 
 scalar_t__* h_attenuation ; 
 TYPE_1__* hps_h_coeff_tab ; 

__attribute__((used)) static int calculate_h_scale_registers(struct saa7146_dev *dev,
	int in_x, int out_x, int flip_lr,
	u32* hps_ctrl, u32* hps_v_gain, u32* hps_h_prescale, u32* hps_h_scale)
{
	/* horizontal prescaler */
	u32 dcgx = 0, xpsc = 0, xacm = 0, cxy = 0, cxuv = 0;
	/* horizontal scaler */
	u32 xim = 0, xp = 0, xsci =0;
	/* vertical scale & gain */
	u32 pfuv = 0;

	/* helper variables */
	u32 h_atten = 0, i = 0;

	if ( 0 == out_x ) {
		return -EINVAL;
	}

	/* mask out vanity-bit */
	*hps_ctrl &= ~MASK_29;

	/* calculate prescale-(xspc)-value:	[n   .. 1/2) : 1
						[1/2 .. 1/3) : 2
						[1/3 .. 1/4) : 3
						...		*/
	if (in_x > out_x) {
		xpsc = in_x / out_x;
	}
	else {
		/* zooming */
		xpsc = 1;
	}

	/* if flip_lr-bit is set, number of pixels after
	   horizontal prescaling must be < 384 */
	if ( 0 != flip_lr ) {

		/* set vanity bit */
		*hps_ctrl |= MASK_29;

		while (in_x / xpsc >= 384 )
			xpsc++;
	}
	/* if zooming is wanted, number of pixels after
	   horizontal prescaling must be < 768 */
	else {
		while ( in_x / xpsc >= 768 )
			xpsc++;
	}

	/* maximum prescale is 64 (p.69) */
	if ( xpsc > 64 )
		xpsc = 64;

	/* keep xacm clear*/
	xacm = 0;

	/* set horizontal filter parameters (CXY = CXUV) */
	cxy = hps_h_coeff_tab[( (xpsc - 1) < 63 ? (xpsc - 1) : 63 )].hps_coeff;
	cxuv = cxy;

	/* calculate and set horizontal fine scale (xsci) */

	/* bypass the horizontal scaler ? */
	if ( (in_x == out_x) && ( 1 == xpsc ) )
		xsci = 0x400;
	else
		xsci = ( (1024 * in_x) / (out_x * xpsc) ) + xpsc;

	/* set start phase for horizontal fine scale (xp) to 0 */
	xp = 0;

	/* set xim, if we bypass the horizontal scaler */
	if ( 0x400 == xsci )
		xim = 1;
	else
		xim = 0;

	/* if the prescaler is bypassed, enable horizontal
	   accumulation mode (xacm) and clear dcgx */
	if( 1 == xpsc ) {
		xacm = 1;
		dcgx = 0;
	} else {
		xacm = 0;
		/* get best match in the table of attenuations
		   for horizontal scaling */
		h_atten = hps_h_coeff_tab[( (xpsc - 1) < 63 ? (xpsc - 1) : 63 )].weight_sum;

		for (i = 0; h_attenuation[i] != 0; i++) {
			if (h_attenuation[i] >= h_atten)
				break;
		}

		dcgx = i;
	}

	/* the horizontal scaling increment controls the UV filter
	   to reduce the bandwidth to improve the display quality,
	   so set it ... */
	if ( xsci == 0x400)
		pfuv = 0x00;
	else if ( xsci < 0x600)
		pfuv = 0x01;
	else if ( xsci < 0x680)
		pfuv = 0x11;
	else if ( xsci < 0x700)
		pfuv = 0x22;
	else
		pfuv = 0x33;


	*hps_v_gain  &= MASK_W0|MASK_B2;
	*hps_v_gain  |= (pfuv << 24);

	*hps_h_scale	&= ~(MASK_W1 | 0xf000);
	*hps_h_scale	|= (xim << 31) | (xp << 24) | (xsci << 12);

	*hps_h_prescale	|= (dcgx << 27) | ((xpsc-1) << 18) | (xacm << 17) | (cxy << 8) | (cxuv << 0);

	return 0;
}