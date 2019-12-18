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
typedef  int uint64_t ;
typedef  int int64_t ;
struct TYPE_4__ {unsigned int index; int frac; int dst_incr; int src_incr; int compensation_distance; unsigned int phase_shift; int filter_length; int ideal_dst_incr; unsigned int phase_mask; int /*<<< orphan*/  (* resample_one ) (TYPE_1__*,void*,int,void const*,unsigned int,int) ;int /*<<< orphan*/  (* resample_nearest ) (void*,int,void const*,int) ;} ;
typedef  TYPE_1__ ResampleContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_BUG ; 
 int /*<<< orphan*/  EINVAL ; 
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  stub1 (void*,int,void const*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,void*,int,void const*,unsigned int,int) ; 

__attribute__((used)) static int resample(ResampleContext *c, void *dst, const void *src,
                    int *consumed, int src_size, int dst_size, int update_ctx,
                    int nearest_neighbour)
{
    int dst_index;
    unsigned int index = c->index;
    int frac          = c->frac;
    int dst_incr_frac = c->dst_incr % c->src_incr;
    int dst_incr      = c->dst_incr / c->src_incr;
    int compensation_distance = c->compensation_distance;

    if (!dst != !src)
        return AVERROR(EINVAL);

    if (nearest_neighbour) {
        uint64_t index2 = ((uint64_t)index) << 32;
        int64_t incr   = (1LL << 32) * c->dst_incr / c->src_incr;
        dst_size       = FFMIN(dst_size,
                               (src_size-1-index) * (int64_t)c->src_incr /
                               c->dst_incr);

        if (dst) {
            for(dst_index = 0; dst_index < dst_size; dst_index++) {
                c->resample_nearest(dst, dst_index, src, index2 >> 32);
                index2 += incr;
            }
        } else {
            dst_index = dst_size;
        }
        index += dst_index * dst_incr;
        index += (frac + dst_index * (int64_t)dst_incr_frac) / c->src_incr;
        frac   = (frac + dst_index * (int64_t)dst_incr_frac) % c->src_incr;
    } else {
        for (dst_index = 0; dst_index < dst_size; dst_index++) {
            int sample_index = index >> c->phase_shift;

            if (sample_index + c->filter_length > src_size)
                break;

            if (dst)
                c->resample_one(c, dst, dst_index, src, index, frac);

            frac  += dst_incr_frac;
            index += dst_incr;
            if (frac >= c->src_incr) {
                frac -= c->src_incr;
                index++;
            }
            if (dst_index + 1 == compensation_distance) {
                compensation_distance = 0;
                dst_incr_frac = c->ideal_dst_incr % c->src_incr;
                dst_incr      = c->ideal_dst_incr / c->src_incr;
            }
        }
    }
    if (consumed)
        *consumed = index >> c->phase_shift;

    if (update_ctx) {
        index &= c->phase_mask;

        if (compensation_distance) {
            compensation_distance -= dst_index;
            if (compensation_distance <= 0)
                return AVERROR_BUG;
        }
        c->frac     = frac;
        c->index    = index;
        c->dst_incr = dst_incr_frac + c->src_incr*dst_incr;
        c->compensation_distance = compensation_distance;
    }

    return dst_index;
}