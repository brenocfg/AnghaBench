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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  draw_line (int /*<<< orphan*/ * const,int const,int,int,int,int,int const,int const,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  monochrome_color_location (int,int const,int const,int const,int*,int*) ; 

__attribute__((used)) static void
tongue_outline(uint16_t* const pixels,
               int       const linesize,
               int       const w,
               int       const h,
               uint16_t  const maxval,
               int       const cie)
{
    const uint16_t rgbcolor[4] = { maxval, maxval, maxval, maxval };
    int wavelength;
    int lx, ly;
    int fx, fy;

    for (wavelength = 360; wavelength <= 830; wavelength++) {
        int icx, icy;

        monochrome_color_location(wavelength, w, h, cie,
                                  &icx, &icy);

        if (wavelength > 360)
            draw_line(pixels, linesize, lx, ly, icx, icy, w, h, rgbcolor);
        else {
            fx = icx;
            fy = icy;
        }
        lx = icx;
        ly = icy;
    }
    draw_line(pixels, linesize, lx, ly, fx, fy, w, h, rgbcolor);
}