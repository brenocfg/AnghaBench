#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int const ptrdiff_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* compute_safe_ssd_integral_image ) (int /*<<< orphan*/ *,int const,int /*<<< orphan*/  const*,int const,int /*<<< orphan*/  const*,int const,int const,int const) ;} ;
typedef  TYPE_1__ NLMeansDSPContext ;

/* Variables and functions */
 int FFMAX (int const,int const) ; 
 int FFMIN (int const,int const) ; 
 int /*<<< orphan*/  av_assert1 (int) ; 
 int /*<<< orphan*/  compute_unsafe_ssd_integral_image (int /*<<< orphan*/ *,int const,int const,int const,int /*<<< orphan*/  const*,int const,int,int,int,int,int,int const,int const) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int const,int /*<<< orphan*/  const*,int const,int /*<<< orphan*/  const*,int const,int const,int const) ; 

__attribute__((used)) static void compute_ssd_integral_image(const NLMeansDSPContext *dsp,
                                       uint32_t *ii, ptrdiff_t ii_linesize_32,
                                       const uint8_t *src, ptrdiff_t linesize, int offx, int offy,
                                       int e, int w, int h)
{
    // ii has a surrounding padding of thickness "e"
    const int ii_w = w + e*2;
    const int ii_h = h + e*2;

    // we center the first source
    const int s1x = e;
    const int s1y = e;

    // 2nd source is the frame with offsetting
    const int s2x = e + offx;
    const int s2y = e + offy;

    // get the dimension of the overlapping rectangle where it is always safe
    // to compare the 2 sources pixels
    const int startx_safe = FFMAX(s1x, s2x);
    const int starty_safe = FFMAX(s1y, s2y);
    const int u_endx_safe = FFMIN(s1x + w, s2x + w); // unaligned
    const int endy_safe   = FFMIN(s1y + h, s2y + h);

    // deduce the safe area width and height
    const int safe_pw = (u_endx_safe - startx_safe) & ~0xf;
    const int safe_ph = endy_safe - starty_safe;

    // adjusted end x position of the safe area after width of the safe area gets aligned
    const int endx_safe = startx_safe + safe_pw;

    // top part where only one of s1 and s2 is still readable, or none at all
    compute_unsafe_ssd_integral_image(ii, ii_linesize_32,
                                      0, 0,
                                      src, linesize,
                                      offx, offy, e, w, h,
                                      ii_w, starty_safe);

    // fill the left column integral required to compute the central
    // overlapping one
    compute_unsafe_ssd_integral_image(ii, ii_linesize_32,
                                      0, starty_safe,
                                      src, linesize,
                                      offx, offy, e, w, h,
                                      startx_safe, safe_ph);

    // main and safe part of the integral
    av_assert1(startx_safe - s1x >= 0); av_assert1(startx_safe - s1x < w);
    av_assert1(starty_safe - s1y >= 0); av_assert1(starty_safe - s1y < h);
    av_assert1(startx_safe - s2x >= 0); av_assert1(startx_safe - s2x < w);
    av_assert1(starty_safe - s2y >= 0); av_assert1(starty_safe - s2y < h);
    if (safe_pw && safe_ph)
        dsp->compute_safe_ssd_integral_image(ii + starty_safe*ii_linesize_32 + startx_safe, ii_linesize_32,
                                             src + (starty_safe - s1y) * linesize + (startx_safe - s1x), linesize,
                                             src + (starty_safe - s2y) * linesize + (startx_safe - s2x), linesize,
                                             safe_pw, safe_ph);

    // right part of the integral
    compute_unsafe_ssd_integral_image(ii, ii_linesize_32,
                                      endx_safe, starty_safe,
                                      src, linesize,
                                      offx, offy, e, w, h,
                                      ii_w - endx_safe, safe_ph);

    // bottom part where only one of s1 and s2 is still readable, or none at all
    compute_unsafe_ssd_integral_image(ii, ii_linesize_32,
                                      0, endy_safe,
                                      src, linesize,
                                      offx, offy, e, w, h,
                                      ii_w, ii_h - endy_safe);
}