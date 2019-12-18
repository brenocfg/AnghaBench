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
typedef  int uint16_t ;
struct ColorSystem {int dummy; } ;

/* Variables and functions */
 double FFMAX3 (double,double,double) ; 
 int const LUV ; 
 int const UCS ; 
 int const XYY ; 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 scalar_t__ constrain_rgb (double*,double*,double*) ; 
 int /*<<< orphan*/  find_tongue (int* const,int const,int const,int,int*,int*,int*) ; 
 int /*<<< orphan*/  gamma_correct_rgb (struct ColorSystem const* const,double*,double*,double*) ; 
 int /*<<< orphan*/  upvp_to_xy (double,double,double*,double*) ; 
 int /*<<< orphan*/  uv_to_xy (double,double,double*,double*) ; 
 int /*<<< orphan*/  xyz_to_rgb (double const**,double,double,double,double*,double*,double*) ; 

__attribute__((used)) static void
fill_in_tongue(uint16_t*                  const pixels,
               int                        const linesize,
               int                        const w,
               int                        const h,
               uint16_t                   const maxval,
               const struct ColorSystem * const cs,
               double                     const m[3][3],
               int                        const cie,
               int                        const correct_gamma,
               float                      const contrast)
{
    int y;

    /* Scan the image line by line and  fill  the  tongue  outline
       with the RGB values determined by the color system for the x-y
       co-ordinates within the tongue.
    */

    for (y = 0; y < h; ++y) {
        int  present;  /* There is some tongue on this line */
        int leftEdge; /* x position of leftmost pixel in tongue on this line */
        int rightEdge; /* same, but rightmost */

        find_tongue(pixels, w, linesize, y, &present, &leftEdge, &rightEdge);

        if (present) {
            int x;

            for (x = leftEdge; x <= rightEdge; ++x) {
                double cx, cy, cz, jr, jg, jb, jmax;
                int r, g, b, mx = maxval;

                if (cie == LUV) {
                    double up, vp;
                    up = ((double) x) / (w - 1);
                    vp = 1.0 - ((double) y) / (h - 1);
                    upvp_to_xy(up, vp, &cx, &cy);
                    cz = 1.0 - (cx + cy);
                } else if (cie == UCS) {
                    double u, v;
                    u = ((double) x) / (w - 1);
                    v = 1.0 - ((double) y) / (h - 1);
                    uv_to_xy(u, v, &cx, &cy);
                    cz = 1.0 - (cx + cy);
                } else if (cie == XYY) {
                    cx = ((double) x) / (w - 1);
                    cy = 1.0 - ((double) y) / (h - 1);
                    cz = 1.0 - (cx + cy);
                } else {
                    av_assert0(0);
                }

                xyz_to_rgb(m, cx, cy, cz, &jr, &jg, &jb);

                /* Check whether the requested color  is  within  the
                   gamut  achievable with the given color system.  If
                   not, draw it in a reduced  intensity,  interpolated
                   by desaturation to the closest within-gamut color. */

                if (constrain_rgb(&jr, &jg, &jb))
                    mx *= contrast;

                jmax = FFMAX3(jr, jg, jb);
                if (jmax > 0) {
                    jr = jr / jmax;
                    jg = jg / jmax;
                    jb = jb / jmax;
                }
                /* gamma correct from linear rgb to nonlinear rgb. */
                if (correct_gamma)
                    gamma_correct_rgb(cs, &jr, &jg, &jb);
                r = mx * jr;
                g = mx * jg;
                b = mx * jb;
                pixels[y * linesize + x * 4 + 0] = r;
                pixels[y * linesize + x * 4 + 1] = g;
                pixels[y * linesize + x * 4 + 2] = b;
                pixels[y * linesize + x * 4 + 3] = 65535;
            }
        }
    }
}