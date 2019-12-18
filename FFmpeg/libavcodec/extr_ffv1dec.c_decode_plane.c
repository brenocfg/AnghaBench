#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int int16_t ;
struct TYPE_6__ {int* sample_buffer; TYPE_1__* avctx; scalar_t__ packed_at_lsb; scalar_t__ run_index; } ;
struct TYPE_5__ {int bits_per_raw_sample; } ;
typedef  TYPE_2__ FFV1Context ;

/* Variables and functions */
 int decode_line (TYPE_2__*,int,int**,int,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int decode_plane(FFV1Context *s, uint8_t *src,
                         int w, int h, int stride, int plane_index,
                         int pixel_stride)
{
    int x, y;
    int16_t *sample[2];
    sample[0] = s->sample_buffer + 3;
    sample[1] = s->sample_buffer + w + 6 + 3;

    s->run_index = 0;

    memset(s->sample_buffer, 0, 2 * (w + 6) * sizeof(*s->sample_buffer));

    for (y = 0; y < h; y++) {
        int16_t *temp = sample[0]; // FIXME: try a normal buffer

        sample[0] = sample[1];
        sample[1] = temp;

        sample[1][-1] = sample[0][0];
        sample[0][w]  = sample[0][w - 1];

// { START_TIMER
        if (s->avctx->bits_per_raw_sample <= 8) {
            int ret = decode_line(s, w, sample, plane_index, 8);
            if (ret < 0)
                return ret;
            for (x = 0; x < w; x++)
                src[x*pixel_stride + stride * y] = sample[1][x];
        } else {
            int ret = decode_line(s, w, sample, plane_index, s->avctx->bits_per_raw_sample);
            if (ret < 0)
                return ret;
            if (s->packed_at_lsb) {
                for (x = 0; x < w; x++) {
                    ((uint16_t*)(src + stride*y))[x*pixel_stride] = sample[1][x];
                }
            } else {
                for (x = 0; x < w; x++) {
                    ((uint16_t*)(src + stride*y))[x*pixel_stride] = sample[1][x] << (16 - s->avctx->bits_per_raw_sample) | ((uint16_t **)sample)[1][x] >> (2 * s->avctx->bits_per_raw_sample - 16);
                }
            }
        }
// STOP_TIMER("decode-line") }
    }
    return 0;
}