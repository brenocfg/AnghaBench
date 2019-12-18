#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct MpegEncContext {int dummy; } ;
typedef  int /*<<< orphan*/  ptrdiff_t ;
struct TYPE_18__ {int member_1; int member_2; int member_3; int /*<<< orphan*/  member_0; } ;
struct TYPE_17__ {int member_1; int member_2; int member_3; int /*<<< orphan*/  member_0; } ;
struct TYPE_16__ {int member_1; int member_2; int member_3; int /*<<< orphan*/  member_0; } ;
struct TYPE_15__ {int member_0; int member_1; int member_2; int member_3; } ;
struct TYPE_14__ {TYPE_9__ member_3; TYPE_8__ member_2; TYPE_7__ member_1; TYPE_6__ member_0; } ;
struct TYPE_13__ {int member_1; int member_2; int member_3; int /*<<< orphan*/  member_0; } ;
struct TYPE_12__ {int member_1; int member_2; int member_3; int /*<<< orphan*/  member_0; } ;
struct TYPE_11__ {int member_0; int member_1; int member_2; int member_3; } ;
struct TYPE_10__ {TYPE_4__ member_2; TYPE_3__ member_1; TYPE_2__ member_0; } ;

/* Variables and functions */
 scalar_t__ FFABS (int) ; 
 int /*<<< orphan*/  av_assert1 (int) ; 
 int /*<<< orphan*/  ff_spatial_dwt (int*,int*,int,int,int,int,int const) ; 

__attribute__((used)) static inline int w_c(struct MpegEncContext *v, uint8_t *pix1, uint8_t *pix2, ptrdiff_t line_size,
                      int w, int h, int type)
{
    int s, i, j;
    const int dec_count = w == 8 ? 3 : 4;
    int tmp[32 * 32], tmp2[32];
    int level, ori;
    static const int scale[2][2][4][4] = {
        {
            { // 9/7 8x8 dec=3
                { 268, 239, 239, 213 },
                { 0,   224, 224, 152 },
                { 0,   135, 135, 110 },
            },
            { // 9/7 16x16 or 32x32 dec=4
                { 344, 310, 310, 280 },
                { 0,   320, 320, 228 },
                { 0,   175, 175, 136 },
                { 0,   129, 129, 102 },
            }
        },
        {
            { // 5/3 8x8 dec=3
                { 275, 245, 245, 218 },
                { 0,   230, 230, 156 },
                { 0,   138, 138, 113 },
            },
            { // 5/3 16x16 or 32x32 dec=4
                { 352, 317, 317, 286 },
                { 0,   328, 328, 233 },
                { 0,   180, 180, 140 },
                { 0,   132, 132, 105 },
            }
        }
    };

    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j += 4) {
            tmp[32 * i + j + 0] = (pix1[j + 0] - pix2[j + 0]) << 4;
            tmp[32 * i + j + 1] = (pix1[j + 1] - pix2[j + 1]) << 4;
            tmp[32 * i + j + 2] = (pix1[j + 2] - pix2[j + 2]) << 4;
            tmp[32 * i + j + 3] = (pix1[j + 3] - pix2[j + 3]) << 4;
        }
        pix1 += line_size;
        pix2 += line_size;
    }

    ff_spatial_dwt(tmp, tmp2, w, h, 32, type, dec_count);

    s = 0;
    av_assert1(w == h);
    for (level = 0; level < dec_count; level++)
        for (ori = level ? 1 : 0; ori < 4; ori++) {
            int size   = w >> (dec_count - level);
            int sx     = (ori & 1) ? size : 0;
            int stride = 32 << (dec_count - level);
            int sy     = (ori & 2) ? stride >> 1 : 0;

            for (i = 0; i < size; i++)
                for (j = 0; j < size; j++) {
                    int v = tmp[sx + sy + i * stride + j] *
                            scale[type][dec_count - 3][level][ori];
                    s += FFABS(v);
                }
        }
    av_assert1(s >= 0);
    return s >> 9;
}