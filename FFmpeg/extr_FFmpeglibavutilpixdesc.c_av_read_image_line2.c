#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_5__ {int plane; int depth; int shift; int step; int offset; } ;
struct TYPE_4__ {int flags; TYPE_2__* comp; } ;
typedef  TYPE_1__ AVPixFmtDescriptor ;
typedef  TYPE_2__ AVComponentDescriptor ;

/* Variables and functions */
 int AV_PIX_FMT_FLAG_BE ; 
 int AV_PIX_FMT_FLAG_BITSTREAM ; 
 unsigned int AV_RB16 (int const*) ; 
 unsigned int AV_RB32 (int const*) ; 
 unsigned int AV_RL16 (int const*) ; 
 unsigned int AV_RL32 (int const*) ; 

void av_read_image_line2(void *dst,
                        const uint8_t *data[4], const int linesize[4],
                        const AVPixFmtDescriptor *desc,
                        int x, int y, int c, int w,
                        int read_pal_component,
                        int dst_element_size)
{
    AVComponentDescriptor comp = desc->comp[c];
    int plane = comp.plane;
    int depth = comp.depth;
    unsigned mask  = (1ULL << depth) - 1;
    int shift = comp.shift;
    int step  = comp.step;
    int flags = desc->flags;
    uint16_t *dst16 = dst;
    uint32_t *dst32 = dst;

    if (flags & AV_PIX_FMT_FLAG_BITSTREAM) {
        int skip = x * step + comp.offset;
        const uint8_t *p = data[plane] + y * linesize[plane] + (skip >> 3);
        int shift = 8 - depth - (skip & 7);

        while (w--) {
            int val = (*p >> shift) & mask;
            if (read_pal_component)
                val = data[1][4*val + c];
            shift -= step;
            p -= shift >> 3;
            shift &= 7;
            if (dst_element_size == 4) *dst32++ = val;
            else                       *dst16++ = val;
        }
    } else {
        const uint8_t *p = data[plane] + y * linesize[plane] +
                           x * step + comp.offset;
        int is_8bit = shift + depth <= 8;
        int is_16bit= shift + depth <=16;

        if (is_8bit)
            p += !!(flags & AV_PIX_FMT_FLAG_BE);

        while (w--) {
            unsigned val;
            if     (is_8bit)  val = *p;
            else if(is_16bit) val = flags & AV_PIX_FMT_FLAG_BE ? AV_RB16(p) : AV_RL16(p);
            else              val = flags & AV_PIX_FMT_FLAG_BE ? AV_RB32(p) : AV_RL32(p);
            val = (val >> shift) & mask;
            if (read_pal_component)
                val = data[1][4 * val + c];
            p += step;
            if (dst_element_size == 4) *dst32++ = val;
            else                       *dst16++ = val;
        }
    }
}