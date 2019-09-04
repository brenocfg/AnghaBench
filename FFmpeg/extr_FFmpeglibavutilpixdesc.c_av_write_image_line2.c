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
typedef  unsigned int uint32_t ;
typedef  unsigned int uint16_t ;
struct TYPE_5__ {int plane; int depth; int step; int offset; int shift; } ;
struct TYPE_4__ {int flags; TYPE_2__* comp; } ;
typedef  TYPE_1__ AVPixFmtDescriptor ;
typedef  TYPE_2__ AVComponentDescriptor ;

/* Variables and functions */
 int AV_PIX_FMT_FLAG_BE ; 
 int AV_PIX_FMT_FLAG_BITSTREAM ; 
 unsigned int AV_RB16 (int*) ; 
 unsigned int AV_RB32 (int*) ; 
 unsigned int AV_RL16 (int*) ; 
 unsigned int AV_RL32 (int*) ; 
 int /*<<< orphan*/  AV_WB16 (int*,unsigned int) ; 
 int /*<<< orphan*/  AV_WB32 (int*,unsigned int) ; 
 int /*<<< orphan*/  AV_WL16 (int*,unsigned int) ; 
 int /*<<< orphan*/  AV_WL32 (int*,unsigned int) ; 

void av_write_image_line2(const void *src,
                         uint8_t *data[4], const int linesize[4],
                         const AVPixFmtDescriptor *desc,
                         int x, int y, int c, int w, int src_element_size)
{
    AVComponentDescriptor comp = desc->comp[c];
    int plane = comp.plane;
    int depth = comp.depth;
    int step  = comp.step;
    int flags = desc->flags;
    const uint32_t *src32 = src;
    const uint16_t *src16 = src;

    if (flags & AV_PIX_FMT_FLAG_BITSTREAM) {
        int skip = x * step + comp.offset;
        uint8_t *p = data[plane] + y * linesize[plane] + (skip >> 3);
        int shift = 8 - depth - (skip & 7);

        while (w--) {
            *p |= (src_element_size == 4 ? *src32++ : *src16++) << shift;
            shift -= step;
            p -= shift >> 3;
            shift &= 7;
        }
    } else {
        int shift = comp.shift;
        uint8_t *p = data[plane] + y * linesize[plane] +
                     x * step + comp.offset;

        if (shift + depth <= 8) {
            p += !!(flags & AV_PIX_FMT_FLAG_BE);
            while (w--) {
                *p |= ((src_element_size == 4 ? *src32++ : *src16++) << shift);
                p += step;
            }
        } else {
            while (w--) {
                unsigned s = (src_element_size == 4 ? *src32++ : *src16++);
                if (shift + depth <= 16) {
                    if (flags & AV_PIX_FMT_FLAG_BE) {
                        uint16_t val = AV_RB16(p) | (s << shift);
                        AV_WB16(p, val);
                    } else {
                        uint16_t val = AV_RL16(p) | (s << shift);
                        AV_WL16(p, val);
                    }
                } else {
                    if (flags & AV_PIX_FMT_FLAG_BE) {
                        uint32_t val = AV_RB32(p) | (s << shift);
                        AV_WB32(p, val);
                    } else {
                        uint32_t val = AV_RL32(p) | (s << shift);
                        AV_WL32(p, val);
                    }
                }
                p += step;
            }
        }
    }
}