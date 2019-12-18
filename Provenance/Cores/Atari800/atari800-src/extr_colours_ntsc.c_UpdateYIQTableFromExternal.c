#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned char* palette; scalar_t__ adjust; } ;
struct TYPE_3__ {double gamma; double contrast; double brightness; } ;

/* Variables and functions */
 TYPE_2__ COLOURS_NTSC_external ; 
 TYPE_1__ COLOURS_NTSC_setup ; 
 double colorburst_angle ; 
 double cos (double) ; 
 double pow (double,double const) ; 
 double sin (double) ; 

__attribute__((used)) static void UpdateYIQTableFromExternal(double yiq_table[768], double start_angle, const double start_saturation)
{
	const double gamma = 1 - COLOURS_NTSC_setup.gamma / 2.0;
	unsigned char *ext_ptr = COLOURS_NTSC_external.palette;
	int n;

	start_angle = - colorburst_angle - start_angle;

	for (n = 0; n < 256; n ++) {
		/* Convert RGB values from external palette to YIQ. */
		double r = (double)*ext_ptr++ / 255.0;
		double g = (double)*ext_ptr++ / 255.0;
		double b = (double)*ext_ptr++ / 255.0;
		double y = 0.299 * r + 0.587 * g + 0.114 * b;
		double i = 0.595716 * r - 0.274453 * g - 0.321263 * b;
		double q = 0.211456 * r - 0.522591 * g + 0.311135 * b;
		double s = sin(start_angle);
		double c = cos(start_angle);
		double tmp_i = i;
		i = tmp_i * c - q * s;
		q = tmp_i * s + q * c;
		/* Optionally adjust external palette. */
		if (COLOURS_NTSC_external.adjust) {
			y = pow(y, gamma);
			y *= COLOURS_NTSC_setup.contrast * 0.5 + 1;
			y += COLOURS_NTSC_setup.brightness * 0.5;
			if (y > 1.0)
				y = 1.0;
			else if (y < 0.0)
				y = 0.0;
			i *= start_saturation + 1;
			q *= start_saturation + 1;
		}

		*yiq_table++ = y;
		*yiq_table++ = i;
		*yiq_table++ = q;
	}
}