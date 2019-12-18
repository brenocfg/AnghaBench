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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  AV_WL32 (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RGBA (int,int,int,unsigned int) ; 
 int /*<<< orphan*/  decompress_indices (int*,int const*) ; 

__attribute__((used)) static inline void rgtc_block_internal(uint8_t *dst, ptrdiff_t stride,
                                       const uint8_t *block,
                                       const int *color_tab, int mono, int offset, int pix_size)
{
    uint8_t indices[16];
    int x, y;

    decompress_indices(indices, block + 2);

    /* Only one or two channels are stored at most, since it only used to
     * compress specular (black and white) or normal (red and green) maps.
     * Although the standard says to zero out unused components, many
     * implementations fill all of them with the same value. */
    for (y = 0; y < 4; y++) {
        for (x = 0; x < 4; x++) {
            int i = indices[x + y * 4];
            /* Interval expansion from [-1 1] or [0 1] to [0 255]. */
            int c = color_tab[i];

            if (mono){
                dst [x * pix_size + y * stride + offset] = (uint8_t)c;
            }
            else{
                uint32_t pixel = RGBA(c, c, c, 255U);
                AV_WL32(dst + x * pix_size + y * stride, pixel);
            }
        }
    }
}