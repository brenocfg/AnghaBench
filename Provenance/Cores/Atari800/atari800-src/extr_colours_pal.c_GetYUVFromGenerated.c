#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_66__   TYPE_9__ ;
typedef  struct TYPE_65__   TYPE_8__ ;
typedef  struct TYPE_64__   TYPE_7__ ;
typedef  struct TYPE_63__   TYPE_6__ ;
typedef  struct TYPE_62__   TYPE_5__ ;
typedef  struct TYPE_61__   TYPE_4__ ;
typedef  struct TYPE_60__   TYPE_3__ ;
typedef  struct TYPE_59__   TYPE_33__ ;
typedef  struct TYPE_58__   TYPE_32__ ;
typedef  struct TYPE_57__   TYPE_31__ ;
typedef  struct TYPE_56__   TYPE_30__ ;
typedef  struct TYPE_55__   TYPE_2__ ;
typedef  struct TYPE_54__   TYPE_29__ ;
typedef  struct TYPE_53__   TYPE_28__ ;
typedef  struct TYPE_52__   TYPE_27__ ;
typedef  struct TYPE_51__   TYPE_26__ ;
typedef  struct TYPE_50__   TYPE_25__ ;
typedef  struct TYPE_49__   TYPE_24__ ;
typedef  struct TYPE_48__   TYPE_23__ ;
typedef  struct TYPE_47__   TYPE_22__ ;
typedef  struct TYPE_46__   TYPE_21__ ;
typedef  struct TYPE_45__   TYPE_20__ ;
typedef  struct TYPE_44__   TYPE_1__ ;
typedef  struct TYPE_43__   TYPE_19__ ;
typedef  struct TYPE_42__   TYPE_18__ ;
typedef  struct TYPE_41__   TYPE_17__ ;
typedef  struct TYPE_40__   TYPE_16__ ;
typedef  struct TYPE_39__   TYPE_15__ ;
typedef  struct TYPE_38__   TYPE_14__ ;
typedef  struct TYPE_37__   TYPE_13__ ;
typedef  struct TYPE_36__   TYPE_12__ ;
typedef  struct TYPE_35__   TYPE_11__ ;
typedef  struct TYPE_34__   TYPE_10__ ;

/* Type definitions */
struct TYPE_66__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_65__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_64__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_63__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_62__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_61__ {int member_0; int member_1; } ;
struct TYPE_60__ {int member_0; int member_1; } ;
struct TYPE_59__ {double gamma; double color_delay; double const hue; int saturation; double contrast; double brightness; scalar_t__ white_level; scalar_t__ black_level; } ;
struct TYPE_58__ {int member_0; int member_1; } ;
struct TYPE_57__ {int member_0; int member_1; } ;
struct TYPE_56__ {int member_0; int member_1; } ;
struct TYPE_55__ {int member_0; int member_1; } ;
struct TYPE_54__ {int member_0; int member_1; } ;
struct TYPE_53__ {int member_0; int member_1; } ;
struct TYPE_52__ {int member_0; int member_1; } ;
struct TYPE_51__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_50__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_49__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_48__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_47__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_46__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_45__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_40__ {int member_0; int member_1; } ;
struct TYPE_39__ {int member_0; int member_1; } ;
struct TYPE_38__ {int member_0; int member_1; } ;
struct TYPE_37__ {int member_0; int member_1; } ;
struct TYPE_36__ {int member_0; int member_1; } ;
struct TYPE_35__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_34__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_44__ {TYPE_16__ member_14; TYPE_15__ member_13; TYPE_14__ member_12; TYPE_13__ member_11; TYPE_12__ member_10; TYPE_11__ member_9; TYPE_10__ member_8; TYPE_9__ member_7; TYPE_8__ member_6; TYPE_7__ member_5; TYPE_6__ member_4; TYPE_5__ member_3; TYPE_4__ member_2; TYPE_3__ member_1; TYPE_2__ member_0; } ;
struct TYPE_43__ {int member_0; int /*<<< orphan*/  member_1; } ;
struct TYPE_42__ {int member_0; int member_1; } ;
struct TYPE_41__ {TYPE_32__ member_14; TYPE_31__ member_13; TYPE_30__ member_12; TYPE_29__ member_11; TYPE_28__ member_10; TYPE_27__ member_9; TYPE_26__ member_8; TYPE_25__ member_7; TYPE_24__ member_6; TYPE_23__ member_5; TYPE_22__ member_4; TYPE_21__ member_3; TYPE_20__ member_2; TYPE_19__ member_1; TYPE_18__ member_0; } ;

/* Variables and functions */
 TYPE_33__ COLOURS_PAL_setup ; 
 double M_PI ; 
 double cos (double) ; 
 scalar_t__ floor (double) ; 
 double pow (double,double const) ; 
 double sin (double) ; 
 double sqrt (double) ; 

__attribute__((used)) static void GetYUVFromGenerated(double yuv_table[256*5])
{
	struct del_coeff {
		int add;
		int mult;
	};

	/* Delay coefficients for each hue. */
	static struct {
		struct del_coeff even[15];
		struct del_coeff odd[15];
	} const del_coeffs = {
		{ { 1, 5 }, /* Hue $1 in even lines */
		  { 1, 6 }, /* Hue $2 in even lines */
		  { 1, 7 },
		  { 0, 0 },
		  { 0, 1 },
		  { 0, 2 },
		  { 0, 4 },
		  { 0, 5 },
		  { 0, 6 },
		  { 0, 7 },
		  { 1, 1 },
		  { 1, 2 },
		  { 1, 3 },
		  { 1, 4 },
		  { 1, 5 } /* Hue $F in even lines */
		},
		{ { 1, 1 }, /* Hue $1 in odd lines */
		  { 1, 0 }, /* Hue $2 in odd lines */
		  { 0, 7 },
		  { 0, 6 },
		  { 0, 5 },
		  { 0, 4 },
		  { 0, 2 },
		  { 0, 1 },
		  { 0, 0 },
		  { 1, 7 },
		  { 1, 5 },
		  { 1, 4 },
		  { 1, 3 },
		  { 1, 2 },
		  { 1, 1 } /* Hue $F in odd lines */
		}
	};
	int cr, lm;

	double const scaled_black_level = (double)COLOURS_PAL_setup.black_level / 255.0f;
	double const scaled_white_level = (double)COLOURS_PAL_setup.white_level / 255.0f;
	double const gamma = 1 - COLOURS_PAL_setup.gamma / 2.0;

	/* NTSC luma multipliers from CGIA.PDF */
	static double const luma_mult[16] = {
		0.6941, 0.7091, 0.7241, 0.7401,
		0.7560, 0.7741, 0.7931, 0.8121,
		0.8260, 0.8470, 0.8700, 0.8930,
		0.9160, 0.9420, 0.9690, 1.0000};

	/* When phase shift between even and odd colorbursts is close to 180 deg, the
	   TV stops interpreting color signal. This value determines how close to 180
	   deg that phase shift must be. It is specific to a TV set. */
	static double const color_disable_threshold = 0.05;
	/* Base delay - 1/4.43MHz * base_del = ca. 95.2ns */
	static double const base_del = 0.421894970414201;
	/* Additional delay - 1/4.43MHz * add_del = ca. 100.7ns */
	static double const add_del = 0.446563064859117;
	/* Delay introduced by the DEL pin voltage. */
	double const del_adj = COLOURS_PAL_setup.color_delay / 360.0;

	/* Phase delays of colorbursts in even and odd lines. They are equal to
	   Hue 1. */
	double const even_burst_del = base_del + add_del * del_coeffs.even[0].add + del_adj * del_coeffs.even[0].mult;
	double const odd_burst_del = base_del + add_del * del_coeffs.odd[0].add + del_adj * del_coeffs.odd[0].mult;

	/* Reciprocal of the recreated subcarrier's amplitude. */
	double saturation_mult;
	/* Phase delay of the recreated amplitude. */
	double subcarrier_del = (even_burst_del + odd_burst_del + COLOURS_PAL_setup.hue) / 2.0;

	/* Phase difference between colorbursts in even and odd lines. */
	double burst_diff = even_burst_del - odd_burst_del;
	burst_diff -= floor(burst_diff); /* Normalize to 0..1. */

	if (burst_diff > 0.5 - color_disable_threshold && burst_diff < 0.5 + color_disable_threshold)
		/* Shift between colorbursts close to 180 deg. Don't produce color. */
		saturation_mult = 0.0;
	else {
		/* Subcarrier is a sum of two waves with equal frequency and amplitude,
		   but phase-shifted by 2pi*burst_diff. The formula is derived from
		   http://2000clicks.com/mathhelp/GeometryTrigEquivPhaseShift.aspx */
		double subcarrier_amplitude = sqrt(2.0 * cos(burst_diff*2.0*M_PI) + 2.0);
		/* Normalise saturation_mult by multiplying by sqrt(2), so that it
		   equals 1.0 when odd & even colorbursts are shifted by 90 deg (ie.
		   burst_diff == 0.25). */
		saturation_mult = sqrt(2.0) / subcarrier_amplitude;
	}

	for (cr = 0; cr < 16; cr ++) {
		double even_u = 0.0;
		double odd_u = 0.0;
		double even_v = 0.0;
		double odd_v = 0.0;
		if (cr) {
			struct del_coeff const *even_delay = &(del_coeffs.even[cr - 1]);
			struct del_coeff const *odd_delay = &(del_coeffs.odd[cr - 1]);
			double even_del = base_del + add_del * even_delay->add + del_adj * even_delay->mult;
			double odd_del = base_del + add_del * odd_delay->add + del_adj * odd_delay->mult;
			double even_angle = (0.5 - (even_del - subcarrier_del)) * 2.0 * M_PI;
			double odd_angle = (0.5 + (odd_del - subcarrier_del)) * 2.0 * M_PI;
			double saturation = (COLOURS_PAL_setup.saturation + 1) * 0.175 * saturation_mult;
			even_u = cos(even_angle) * saturation;
			even_v = sin(even_angle) * saturation;
			odd_u = cos(odd_angle) * saturation;
			odd_v = sin(odd_angle) * saturation;
		}
		for (lm = 0; lm < 16; lm ++) {
			/* calculate yuv for color entry */
			double y = (luma_mult[lm] - luma_mult[0]) / (luma_mult[15] - luma_mult[0]);
			y = pow(y, gamma);
			y *= COLOURS_PAL_setup.contrast * 0.5 + 1;
			y += COLOURS_PAL_setup.brightness * 0.5;
			/* Scale the Y signal's range from 0..1 to
			   scaled_black_level..scaled_white_level */
			y = y * (scaled_white_level - scaled_black_level) + scaled_black_level;
			/*
			if (y < scaled_black_level)
				y = scaled_black_level;
			else if (y > scaled_white_level)
				y = scaled_white_level;
			*/
			*yuv_table++ = y;
			*yuv_table++ = even_u;
			*yuv_table++ = odd_u;
			*yuv_table++ = even_v;
			*yuv_table++ = odd_v;
		}
	}
}