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

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AV_RB16 (int const*) ; 
 int AV_RB24 (int const*) ; 
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  av_memcpy_backptr (int*,int,int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 

__attribute__((used)) static int unpack(const uint8_t *src, const uint8_t *src_end,
                  uint8_t *dst, int width, int height)
{
    uint8_t *dst_end = dst + width*height;
    int size, size1, size2, offset, run;
    uint8_t *dst_start = dst;

    if (src[0] & 0x01)
        src += 5;
    else
        src += 2;

    if (src_end - src < 3)
        return AVERROR_INVALIDDATA;
    size = AV_RB24(src);
    src += 3;

    while (size > 0 && src < src_end) {

        /* determine size1 and size2 */
        size1 = (src[0] & 3);
        if (src[0] & 0x80) {  // 1
            if (src[0] & 0x40 ) {  // 11
                if (src[0] & 0x20) {  // 111
                    if (src[0] < 0xFC)  // !(111111)
                        size1 = (((src[0] & 31) + 1) << 2);
                    src++;
                    size2 = 0;
                } else {  // 110
                    offset = ((src[0] & 0x10) << 12) + AV_RB16(&src[1]) + 1;
                    size2  = ((src[0] & 0xC) << 6) + src[3] + 5;
                    src   += 4;
                }
            } else {  // 10
                size1  = ((src[1] & 0xC0) >> 6);
                offset = (AV_RB16(&src[1]) & 0x3FFF) + 1;
                size2  = (src[0] & 0x3F) + 4;
                src   += 3;
            }
        } else {  // 0
            offset = ((src[0] & 0x60) << 3) + src[1] + 1;
            size2  = ((src[0] & 0x1C) >> 2) + 3;
            src   += 2;
        }


        /* fetch strip from src */
        if (size1 > src_end - src)
            break;

        if (size1 > 0) {
            size -= size1;
            run   = FFMIN(size1, dst_end - dst);
            memcpy(dst, src, run);
            dst += run;
            src += run;
        }

        if (size2 > 0) {
            if (dst - dst_start < offset)
                return 0;
            size -= size2;
            run   = FFMIN(size2, dst_end - dst);
            av_memcpy_backptr(dst, offset, run);
            dst += run;
        }
    }

    return 0;
}