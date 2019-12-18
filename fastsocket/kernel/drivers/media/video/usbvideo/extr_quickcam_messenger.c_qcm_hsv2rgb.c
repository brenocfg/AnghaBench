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
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static void qcm_hsv2rgb(u16 hue, u16 sat, u16 val, u16 *r, u16 *g, u16 *b)
{
	unsigned int segment, valsat;
	signed int   h = (signed int) hue;
	unsigned int s = (sat - 32768) * 2;	/* rescale */
	unsigned int v = val;
	unsigned int p;

	/*
	the registers controlling gain are 8 bit of which
	we affect only the last 4 bits with our gain.
	we know that if saturation is 0, (unsaturated) then
	we're grayscale (center axis of the colour cone) so
	we set rgb=value. we use a formula obtained from
	wikipedia to map the cone to the RGB plane. it's
	as follows for the human value case of h=0..360,
	s=0..1, v=0..1
	h_i = h/60 % 6 , f = h/60 - h_i , p = v(1-s)
	q = v(1 - f*s) , t = v(1 - (1-f)s)
	h_i==0 => r=v , g=t, b=p
	h_i==1 => r=q , g=v, b=p
	h_i==2 => r=p , g=v, b=t
	h_i==3 => r=p , g=q, b=v
	h_i==4 => r=t , g=p, b=v
	h_i==5 => r=v , g=p, b=q
	the bottom side (the point) and the stuff just up
	of that is black so we simplify those two cases.
	*/
	if (sat < 32768) {
		/* anything less than this is unsaturated */
		*r = val;
		*g = val;
		*b = val;
		return;
	}
	if (val <= (0xFFFF/8)) {
		/* anything less than this is black */
		*r = 0;
		*g = 0;
		*b = 0;
		return;
	}

	/* the rest of this code is copying tukkat's
	implementation of the hsv2rgb conversion as taken
	from qc-usb-messenger code. the 10923 is 0xFFFF/6
	to divide the cone into 6 sectors.  */

	segment = (h + 10923) & 0xFFFF;
	segment = segment*3 >> 16;		/* 0..2: 0=R, 1=G, 2=B */
	hue -= segment * 21845;			/* -10923..10923 */
	h = hue;
	h *= 3;
	valsat = v*s >> 16;			/* 0..65534 */
	p = v - valsat;
	if (h >= 0) {
		unsigned int t = v - (valsat * (32769 - h) >> 15);
		switch (segment) {
		case 0:	/* R-> */
			*r = v;
			*g = t;
			*b = p;
			break;
		case 1:	/* G-> */
			*r = p;
			*g = v;
			*b = t;
			break;
		case 2:	/* B-> */
			*r = t;
			*g = p;
			*b = v;
			break;
		}
	} else {
		unsigned int q = v - (valsat * (32769 + h) >> 15);
		switch (segment) {
		case 0:	/* ->R */
			*r = v;
			*g = p;
			*b = q;
			break;
		case 1:	/* ->G */
			*r = q;
			*g = v;
			*b = p;
			break;
		case 2:	/* ->B */
			*r = p;
			*g = q;
			*b = v;
			break;
		}
	}
}