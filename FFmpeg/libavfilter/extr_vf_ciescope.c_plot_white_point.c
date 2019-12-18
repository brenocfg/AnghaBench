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
struct ColorSystem {int const xWhite; int const yWhite; } ;

/* Variables and functions */
 int const LUV ; 
 int Sz (int) ; 
 int const UCS ; 
 int const XYY ; 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 struct ColorSystem* color_systems ; 
 int /*<<< orphan*/  draw_rline (int /*<<< orphan*/ *,int const,int,int,int,int,int const,int const) ; 
 int /*<<< orphan*/  xy_to_upvp (int const,int const,double*,double*) ; 
 int /*<<< orphan*/  xy_to_uv (int const,int const,double*,double*) ; 

__attribute__((used)) static void
plot_white_point(uint16_t*      pixels,
                 int      const linesize,
                 int      const w,
                 int      const h,
                 int      const maxval,
                 int      const color_system,
                 int      const cie)
{
    const struct ColorSystem *cs = &color_systems[color_system];
    int wx, wy;

    if (cie == LUV) {
        double wup, wvp;
        xy_to_upvp(cs->xWhite, cs->yWhite, &wup, &wvp);
        wx = (w - 1) * wup;
        wy = (h - 1) - ((int) ((h - 1) * wvp));
    } else if (cie == UCS) {
        double wu, wv;
        xy_to_uv(cs->xWhite, cs->yWhite, &wu, &wv);
        wx = (w - 1) * wu;
        wy = (h - 1) - ((int) ((h - 1) * wv));
    } else if (cie == XYY) {
        wx = (w - 1) * cs->xWhite;
        wy = (h - 1) - ((int) ((h - 1) * cs->yWhite));
    } else {
        av_assert0(0);
    }

    draw_rline(pixels, linesize,
               wx + Sz(3), wy, wx + Sz(10), wy,
               w, h);
    draw_rline(pixels, linesize,
               wx - Sz(3), wy, wx - Sz(10), wy,
               w, h);
    draw_rline(pixels, linesize,
               wx, wy + Sz(3), wx, wy + Sz(10),
               w, h);
    draw_rline(pixels, linesize,
               wx, wy - Sz(3), wx, wy - Sz(10),
               w, h);
}