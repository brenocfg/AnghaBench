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
typedef  int /*<<< orphan*/  int16_t ;
typedef  int /*<<< orphan*/  FDCTDSPContext ;

/* Variables and functions */
 int /*<<< orphan*/  fdct_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void calc_plane_dct(FDCTDSPContext *fdsp, uint8_t *src, int16_t * blocks, int src_stride, int mb_count, int chroma, int is_422)
{
    int16_t *block;
    int i;

    block = blocks;

    if (!chroma) { /* Luma plane */
        for (i = 0; i < mb_count; i++) {
            fdct_get(fdsp, src,                       src_stride, block + (0 << 6));
            fdct_get(fdsp, src + 16,                  src_stride, block + (1 << 6));
            fdct_get(fdsp, src +      8 * src_stride, src_stride, block + (2 << 6));
            fdct_get(fdsp, src + 16 + 8 * src_stride, src_stride, block + (3 << 6));

            block += 256;
            src   += 32;
        }
    } else if (chroma && is_422){ /* chroma plane 422 */
        for (i = 0; i < mb_count; i++) {
            fdct_get(fdsp, src,                  src_stride, block + (0 << 6));
            fdct_get(fdsp, src + 8 * src_stride, src_stride, block + (1 << 6));
            block += (256 >> 1);
            src   += (32  >> 1);
        }
    } else { /* chroma plane 444 */
        for (i = 0; i < mb_count; i++) {
            fdct_get(fdsp, src,                       src_stride, block + (0 << 6));
            fdct_get(fdsp, src +      8 * src_stride, src_stride, block + (1 << 6));
            fdct_get(fdsp, src + 16,                  src_stride, block + (2 << 6));
            fdct_get(fdsp, src + 16 + 8 * src_stride, src_stride, block + (3 << 6));

            block += 256;
            src   += 32;
        }
    }
}