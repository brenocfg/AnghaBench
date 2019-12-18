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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_3__ {int* buf; int thresh; int /*<<< orphan*/  (* filter_line ) (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int*,int,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* blur_line ) (int*,int*,int*,int /*<<< orphan*/  const*,int,int) ;} ;
typedef  TYPE_1__ GradFunContext ;

/* Variables and functions */
 int FFALIGN (int,int) ; 
 int /*<<< orphan*/ * dither ; 
 int /*<<< orphan*/  emms_c () ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int*,int*,int*,int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  stub2 (int*,int*,int*,int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void filter(GradFunContext *ctx, uint8_t *dst, const uint8_t *src, int width, int height, int dst_linesize, int src_linesize, int r)
{
    int bstride = FFALIGN(width, 16) / 2;
    int y;
    uint32_t dc_factor = (1 << 21) / (r * r);
    uint16_t *dc = ctx->buf + 16;
    uint16_t *buf = ctx->buf + bstride + 32;
    int thresh = ctx->thresh;

    memset(dc, 0, (bstride + 16) * sizeof(*buf));
    for (y = 0; y < r; y++)
        ctx->blur_line(dc, buf + y * bstride, buf + (y - 1) * bstride, src + 2 * y * src_linesize, src_linesize, width / 2);
    for (;;) {
        if (y < height - r) {
            int mod = ((y + r) / 2) % r;
            uint16_t *buf0 = buf + mod * bstride;
            uint16_t *buf1 = buf + (mod ? mod - 1 : r - 1) * bstride;
            int x, v;
            ctx->blur_line(dc, buf0, buf1, src + (y + r) * src_linesize, src_linesize, width / 2);
            for (x = v = 0; x < r; x++)
                v += dc[x];
            for (; x < width / 2; x++) {
                v += dc[x] - dc[x-r];
                dc[x-r] = v * dc_factor >> 16;
            }
            for (; x < (width + r + 1) / 2; x++)
                dc[x-r] = v * dc_factor >> 16;
            for (x = -r / 2; x < 0; x++)
                dc[x] = dc[0];
        }
        if (y == r) {
            for (y = 0; y < r; y++)
                ctx->filter_line(dst + y * dst_linesize, src + y * src_linesize, dc - r / 2, width, thresh, dither[y & 7]);
        }
        ctx->filter_line(dst + y * dst_linesize, src + y * src_linesize, dc - r / 2, width, thresh, dither[y & 7]);
        if (++y >= height) break;
        ctx->filter_line(dst + y * dst_linesize, src + y * src_linesize, dc - r / 2, width, thresh, dither[y & 7]);
        if (++y >= height) break;
    }
    emms_c();
}