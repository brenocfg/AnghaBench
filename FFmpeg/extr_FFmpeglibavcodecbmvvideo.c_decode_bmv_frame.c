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
 int FFABS (int) ; 
 int /*<<< orphan*/  NEXT_BYTE (int const*) ; 
 int SCREEN_HIGH ; 
 int SCREEN_WIDE ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int /*<<< orphan*/  memset (int*,unsigned int,int) ; 

__attribute__((used)) static int decode_bmv_frame(const uint8_t *source, int src_len, uint8_t *frame, int frame_off)
{
    unsigned val, saved_val = 0;
    int tmplen = src_len;
    const uint8_t *src, *source_end = source + src_len;
    uint8_t *frame_end = frame + SCREEN_WIDE * SCREEN_HIGH;
    uint8_t *dst, *dst_end;
    int len, mask;
    int forward = (frame_off <= -SCREEN_WIDE) || (frame_off >= 0);
    int read_two_nibbles, flag;
    int advance_mode;
    int mode = 0;
    int i;

    if (src_len <= 0)
        return AVERROR_INVALIDDATA;

    if (forward) {
        src = source;
        dst = frame;
        dst_end = frame_end;
    } else {
        src = source + src_len - 1;
        dst = frame_end - 1;
        dst_end = frame - 1;
    }
    for (;;) {
        int shift = 0;
        flag = 0;

        /* The mode/len decoding is a bit strange:
         * values are coded as variable-length codes with nibble units,
         * code end is signalled by two top bits in the nibble being nonzero.
         * And since data is bytepacked and we read two nibbles at a time,
         * we may get a nibble belonging to the next code.
         * Hence this convoluted loop.
         */
        if (!mode || (tmplen == 4)) {
            if (src < source || src >= source_end)
                return AVERROR_INVALIDDATA;
            val = *src;
            read_two_nibbles = 1;
        } else {
            val = saved_val;
            read_two_nibbles = 0;
        }
        if (!(val & 0xC)) {
            for (;;) {
                if(shift>22)
                    return -1;
                if (!read_two_nibbles) {
                    if (src < source || src >= source_end)
                        return AVERROR_INVALIDDATA;
                    shift += 2;
                    val |= (unsigned)*src << shift;
                    if (*src & 0xC)
                        break;
                }
                // two upper bits of the nibble is zero,
                // so shift top nibble value down into their place
                read_two_nibbles = 0;
                shift += 2;
                mask = (1 << shift) - 1;
                val = ((val >> 2) & ~mask) | (val & mask);
                NEXT_BYTE(src);
                if ((val & (0xC << shift))) {
                    flag = 1;
                    break;
                }
            }
        } else if (mode) {
            flag = tmplen != 4;
        }
        if (flag) {
            tmplen = 4;
        } else {
            saved_val = val >> (4 + shift);
            tmplen = 0;
            val &= (1 << (shift + 4)) - 1;
            NEXT_BYTE(src);
        }
        advance_mode = val & 1;
        len = (val >> 1) - 1;
        av_assert0(len>0);
        mode += 1 + advance_mode;
        if (mode >= 4)
            mode -= 3;
        if (len <= 0 || FFABS(dst_end - dst) < len)
            return AVERROR_INVALIDDATA;
        switch (mode) {
        case 1:
            if (forward) {
                if (dst - frame + SCREEN_WIDE < frame_off ||
                        dst - frame + SCREEN_WIDE + frame_off < 0 ||
                        frame_end - dst < frame_off + len ||
                        frame_end - dst < len)
                    return AVERROR_INVALIDDATA;
                for (i = 0; i < len; i++)
                    dst[i] = dst[frame_off + i];
                dst += len;
            } else {
                dst -= len;
                if (dst - frame + SCREEN_WIDE < frame_off ||
                        dst - frame + SCREEN_WIDE + frame_off < 0 ||
                        frame_end - dst < frame_off + len ||
                        frame_end - dst < len)
                    return AVERROR_INVALIDDATA;
                for (i = len - 1; i >= 0; i--)
                    dst[i] = dst[frame_off + i];
            }
            break;
        case 2:
            if (forward) {
                if (source + src_len - src < len)
                    return AVERROR_INVALIDDATA;
                memcpy(dst, src, len);
                dst += len;
                src += len;
            } else {
                if (src - source < len)
                    return AVERROR_INVALIDDATA;
                dst -= len;
                src -= len;
                memcpy(dst, src, len);
            }
            break;
        case 3:
            val = forward ? dst[-1] : dst[1];
            if (forward) {
                memset(dst, val, len);
                dst += len;
            } else {
                dst -= len;
                memset(dst, val, len);
            }
            break;
        }
        if (dst == dst_end)
            return 0;
    }
}