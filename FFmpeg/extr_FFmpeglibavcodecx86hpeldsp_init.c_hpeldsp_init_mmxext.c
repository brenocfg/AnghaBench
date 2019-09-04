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
typedef  int /*<<< orphan*/  HpelDSPContext ;

/* Variables and functions */

__attribute__((used)) static void hpeldsp_init_mmxext(HpelDSPContext *c, int flags)
{
#if HAVE_MMXEXT_EXTERNAL
    c->put_pixels_tab[0][1] = ff_put_pixels16_x2_mmxext;
    c->put_pixels_tab[0][2] = put_pixels16_y2_mmxext;

    c->avg_pixels_tab[0][0] = avg_pixels16_mmxext;
    c->avg_pixels_tab[0][1] = avg_pixels16_x2_mmxext;
    c->avg_pixels_tab[0][2] = avg_pixels16_y2_mmxext;
    c->avg_pixels_tab[0][3] = avg_pixels16_xy2_mmxext;

    c->put_pixels_tab[1][1] = ff_put_pixels8_x2_mmxext;
    c->put_pixels_tab[1][2] = ff_put_pixels8_y2_mmxext;

    c->avg_pixels_tab[1][0] = ff_avg_pixels8_mmxext;
    c->avg_pixels_tab[1][1] = ff_avg_pixels8_x2_mmxext;
    c->avg_pixels_tab[1][2] = ff_avg_pixels8_y2_mmxext;
    c->avg_pixels_tab[1][3] = ff_avg_pixels8_xy2_mmxext;

    if (!(flags & AV_CODEC_FLAG_BITEXACT)) {
        c->put_no_rnd_pixels_tab[0][1] = put_no_rnd_pixels16_x2_mmxext;
        c->put_no_rnd_pixels_tab[0][2] = put_no_rnd_pixels16_y2_mmxext;
        c->put_no_rnd_pixels_tab[1][1] = ff_put_no_rnd_pixels8_x2_mmxext;
        c->put_no_rnd_pixels_tab[1][2] = ff_put_no_rnd_pixels8_y2_mmxext;

        c->avg_pixels_tab[0][3] = avg_approx_pixels16_xy2_mmxext;
        c->avg_pixels_tab[1][3] = ff_avg_approx_pixels8_xy2_mmxext;
    }
#endif /* HAVE_MMXEXT_EXTERNAL */
}