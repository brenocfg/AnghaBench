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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  ana_convert (int const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void anaglyph_ic(uint8_t *dst, uint8_t *lsrc, uint8_t *rsrc,
                        ptrdiff_t dst_linesize, ptrdiff_t l_linesize, ptrdiff_t r_linesize,
                        int width, int height,
                        const int *ana_matrix_r, const int *ana_matrix_g, const int *ana_matrix_b)
{
    int x, y, o;

    for (y = 0; y < height; y++) {
        for (o = 0, x = 0; x < width; x++, o+= 3) {
            dst[o    ] = ana_convert(ana_matrix_r, lsrc + o * 2, rsrc + o * 2);
            dst[o + 1] = ana_convert(ana_matrix_g, lsrc + o * 2, rsrc + o * 2);
            dst[o + 2] = ana_convert(ana_matrix_b, lsrc + o * 2, rsrc + o * 2);
        }

        dst  += dst_linesize;
        lsrc += l_linesize;
        rsrc += r_linesize;
    }
}