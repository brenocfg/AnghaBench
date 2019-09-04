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
struct ColorSystem {int xRed; int yRed; int xGreen; int yGreen; int xBlue; int yBlue; } ;

/* Variables and functions */
 int LUV ; 
 int NB_CS ; 
 int UCS ; 
 int XYY ; 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 struct ColorSystem* color_systems ; 
 int /*<<< orphan*/  draw_rline (int /*<<< orphan*/ *,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  xy_to_upvp (int,int,double*,double*) ; 
 int /*<<< orphan*/  xy_to_uv (int,int,double*,double*) ; 

__attribute__((used)) static void plot_gamuts(uint16_t *pixels, int linesize, int w, int h,
                        int cie, int gamuts)
{
    int i;

    for (i = 0; i < NB_CS; i++) {
        const struct ColorSystem *cs = &color_systems[i];
        int rx, ry, gx, gy, bx, by;

        if (!((1 << i) & gamuts))
            continue;
        if (cie == LUV) {
            double wup, wvp;
            xy_to_upvp(cs->xRed, cs->yRed, &wup, &wvp);
            rx = (w - 1) * wup;
            ry = (h - 1) - ((int) ((h - 1) * wvp));
            xy_to_upvp(cs->xGreen, cs->yGreen, &wup, &wvp);
            gx = (w - 1) * wup;
            gy = (h - 1) - ((int) ((h - 1) * wvp));
            xy_to_upvp(cs->xBlue, cs->yBlue, &wup, &wvp);
            bx = (w - 1) * wup;
            by = (h - 1) - ((int) ((h - 1) * wvp));
        } else if (cie == UCS) {
            double wu, wv;
            xy_to_uv(cs->xRed, cs->yRed, &wu, &wv);
            rx = (w - 1) * wu;
            ry = (h - 1) - ((int) ((h - 1) * wv));
            xy_to_uv(cs->xGreen, cs->yGreen, &wu, &wv);
            gx = (w - 1) * wu;
            gy = (h - 1) - ((int) ((h - 1) * wv));
            xy_to_uv(cs->xBlue, cs->yBlue, &wu, &wv);
            bx = (w - 1) * wu;
            by = (h - 1) - ((int) ((h - 1) * wv));
        } else if (cie == XYY) {
            rx = (w - 1) * cs->xRed;
            ry = (h - 1) - ((int) ((h - 1) * cs->yRed));
            gx = (w - 1) * cs->xGreen;
            gy = (h - 1) - ((int) ((h - 1) * cs->yGreen));
            bx = (w - 1) * cs->xBlue;
            by = (h - 1) - ((int) ((h - 1) * cs->yBlue));
        } else {
            av_assert0(0);
        }

        draw_rline(pixels, linesize, rx, ry, gx, gy, w, h);
        draw_rline(pixels, linesize, gx, gy, bx, by, w, h);
        draw_rline(pixels, linesize, bx, by, rx, ry, w, h);
    }
}