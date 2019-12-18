#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int ptrdiff_t ;
struct TYPE_10__ {TYPE_3__* sps; TYPE_1__* pps; } ;
struct TYPE_11__ {TYPE_4__ ps; scalar_t__* is_pcm; } ;
struct TYPE_8__ {scalar_t__ loop_filter_disable_flag; } ;
struct TYPE_9__ {int log2_min_pu_size; int* hshift; int* vshift; int pixel_shift; int min_pu_width; scalar_t__ pcm_enabled_flag; TYPE_2__ pcm; } ;
struct TYPE_7__ {scalar_t__ transquant_bypass_enable_flag; } ;
typedef  TYPE_5__ HEVCContext ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void restore_tqb_pixels(HEVCContext *s,
                               uint8_t *src1, const uint8_t *dst1,
                               ptrdiff_t stride_src, ptrdiff_t stride_dst,
                               int x0, int y0, int width, int height, int c_idx)
{
    if ( s->ps.pps->transquant_bypass_enable_flag ||
            (s->ps.sps->pcm.loop_filter_disable_flag && s->ps.sps->pcm_enabled_flag)) {
        int x, y;
        int min_pu_size  = 1 << s->ps.sps->log2_min_pu_size;
        int hshift       = s->ps.sps->hshift[c_idx];
        int vshift       = s->ps.sps->vshift[c_idx];
        int x_min        = ((x0         ) >> s->ps.sps->log2_min_pu_size);
        int y_min        = ((y0         ) >> s->ps.sps->log2_min_pu_size);
        int x_max        = ((x0 + width ) >> s->ps.sps->log2_min_pu_size);
        int y_max        = ((y0 + height) >> s->ps.sps->log2_min_pu_size);
        int len          = (min_pu_size >> hshift) << s->ps.sps->pixel_shift;
        for (y = y_min; y < y_max; y++) {
            for (x = x_min; x < x_max; x++) {
                if (s->is_pcm[y * s->ps.sps->min_pu_width + x]) {
                    int n;
                    uint8_t *src = src1 + (((y << s->ps.sps->log2_min_pu_size) - y0) >> vshift) * stride_src + ((((x << s->ps.sps->log2_min_pu_size) - x0) >> hshift) << s->ps.sps->pixel_shift);
                    const uint8_t *dst = dst1 + (((y << s->ps.sps->log2_min_pu_size) - y0) >> vshift) * stride_dst + ((((x << s->ps.sps->log2_min_pu_size) - x0) >> hshift) << s->ps.sps->pixel_shift);
                    for (n = 0; n < (min_pu_size >> vshift); n++) {
                        memcpy(src, dst, len);
                        src += stride_src;
                        dst += stride_dst;
                    }
                }
            }
        }
    }
}