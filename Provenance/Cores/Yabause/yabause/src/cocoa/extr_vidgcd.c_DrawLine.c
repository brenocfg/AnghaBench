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
struct TYPE_2__ {double r; double g; double b; } ;

/* Variables and functions */
 int currentPixel ; 
 scalar_t__ getpixel (double,int) ; 
 TYPE_1__ leftColumnColor ; 
 int /*<<< orphan*/  putpixel (int,int) ; 

__attribute__((used)) static int DrawLine( int x1, int y1, int x2, int y2, double linenumber, double texturestep, double xredstep, double xgreenstep, double xbluestep)
{
	int dx, dy, xf, yf, a, b, c, i;
	int endcodesdetected=0;
	int previousStep = 123456789;

	if (x2>x1) {
		dx = x2-x1;
		xf = 1;
	}
	else {
		dx = x1-x2;
		xf = -1;
	}

	if (y2>y1) {
		dy = y2-y1;
		yf = 1;
	}
	else {
		dy = y1-y2;
		yf = -1;
	}

	if (dx>dy) {
		a = dy+dy;
		c = a-dx;
		b = c-dx;
		for (i=0;i<=dx;i++) {
			leftColumnColor.r+=xredstep;
			leftColumnColor.g+=xgreenstep;
			leftColumnColor.b+=xbluestep;

			if(getpixel(linenumber,(int)i*texturestep)) {
				if(currentPixel != previousStep) {
					previousStep = (int)i*texturestep;
					endcodesdetected++;
				}
			}
			else
				putpixel(x1,y1);

			previousStep = currentPixel;

			if(endcodesdetected==2)
				break;

			x1 += xf;
			if (c<0) {
				c += a;
			}
			else {
				getpixel(linenumber,(int)i*texturestep);
				putpixel(x1,y1);
				c += b;
				y1 += yf;
/*
				//same as sega's way, but just move the code down here instead
				//and use the pixel we already have instead of the next one
				if(xf>1&&yf>1) putpixel(x1,y1-1); //case 1
				if(xf<1&&yf<1) putpixel(x1,y1+1); //case 2
				if(xf<1&&yf>1) putpixel(x1+1,y1); //case 7
				if(xf>1&&yf<1) putpixel(x1-1,y1); //case 8*/
			}
		}
		return dx+1;
	}
	else {
		a = dx+dx;
		c = a-dy;
		b = c-dy;
	for (i=0;i<=dy;i++) {
			leftColumnColor.r+=xredstep;
			leftColumnColor.g+=xgreenstep;
			leftColumnColor.b+=xbluestep;

			if(getpixel(linenumber,(int)i*texturestep)) {
				if(currentPixel != previousStep) {
					previousStep = (int)i*texturestep;
					endcodesdetected++;
				}
			}
			else
				putpixel(x1,y1);

			previousStep = currentPixel;

			if(endcodesdetected==2)
				break;

			y1 += yf;
			if (c<0) {
				c += a;
			}
			else {
				getpixel(linenumber,(int)i*texturestep);
				putpixel(x1,y1);
				c += b;
				x1 += xf;
/*
				if(xf>1&&yf>1) putpixel(x1,y1-1); //case 3
				if(xf<1&&yf<1) putpixel(x1,y1+1); //case 4
				if(xf<1&&yf>1) putpixel(x1+1,y1); //case 5
				if(xf>1&&yf<1) putpixel(x1-1,y1); //case 6*/

			}
		}
		return dy+1;
	}
}