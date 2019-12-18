#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int int16_t ;
struct TYPE_4__ {int* sample_buffer; int bits_per_raw_sample; scalar_t__ packed_at_lsb; scalar_t__ run_index; scalar_t__ context_model; } ;
typedef  TYPE_1__ FFV1Context ;

/* Variables and functions */
 int encode_line (TYPE_1__*,int,int**,int,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static int encode_plane(FFV1Context *s, uint8_t *src, int w, int h,
                         int stride, int plane_index, int pixel_stride)
{
    int x, y, i, ret;
    const int ring_size = s->context_model ? 3 : 2;
    int16_t *sample[3];
    s->run_index = 0;

    memset(s->sample_buffer, 0, ring_size * (w + 6) * sizeof(*s->sample_buffer));

    for (y = 0; y < h; y++) {
        for (i = 0; i < ring_size; i++)
            sample[i] = s->sample_buffer + (w + 6) * ((h + i - y) % ring_size) + 3;

        sample[0][-1]= sample[1][0  ];
        sample[1][ w]= sample[1][w-1];
// { START_TIMER
        if (s->bits_per_raw_sample <= 8) {
            for (x = 0; x < w; x++)
                sample[0][x] = src[x * pixel_stride + stride * y];
            if((ret = encode_line(s, w, sample, plane_index, 8)) < 0)
                return ret;
        } else {
            if (s->packed_at_lsb) {
                for (x = 0; x < w; x++) {
                    sample[0][x] = ((uint16_t*)(src + stride*y))[x];
                }
            } else {
                for (x = 0; x < w; x++) {
                    sample[0][x] = ((uint16_t*)(src + stride*y))[x] >> (16 - s->bits_per_raw_sample);
                }
            }
            if((ret = encode_line(s, w, sample, plane_index, s->bits_per_raw_sample)) < 0)
                return ret;
        }
// STOP_TIMER("encode line") }
    }
    return 0;
}