#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ size_in_bits; } ;
typedef  int SUINT ;
typedef  TYPE_1__ GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSE_READER (int /*<<< orphan*/ ,TYPE_1__*) ; 
 unsigned int GET_CACHE (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  LAST_SKIP_BITS (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int MIN_CACHE_BITS ; 
 int /*<<< orphan*/  OPEN_READER (int /*<<< orphan*/ ,TYPE_1__*) ; 
 unsigned int SHOW_UBITS (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  SKIP_BITS (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  UPDATE_CACHE (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  av_assert2 (int) ; 
 int av_log2 (unsigned int) ; 
 scalar_t__ get_bits1 (TYPE_1__*) ; 
 scalar_t__ get_bits_left (TYPE_1__*) ; 
 unsigned int get_bits_long (TYPE_1__*,int) ; 
 int /*<<< orphan*/  re ; 
 scalar_t__ re_index ; 
 unsigned int show_bits_long (TYPE_1__*,int) ; 
 int /*<<< orphan*/  skip_bits_long (TYPE_1__*,int) ; 

__attribute__((used)) static inline int get_ur_golomb_jpegls(GetBitContext *gb, int k, int limit,
                                       int esc_len)
{
    unsigned int buf;
    int log;

#if CACHED_BITSTREAM_READER
    buf = show_bits_long(gb, 32);

    log = av_log2(buf);

    if (log - k >= 1 && 32 - log < limit) {
        buf >>= log - k;
        buf  += (30 - log) << k;
        skip_bits_long(gb, 32 + k - log);

        return buf;
    } else {
        int i;
        for (i = 0;
             i < limit && get_bits1(gb) == 0 && get_bits_left(gb) > 0;
             i++);

        if (i < limit - 1) {
            buf = get_bits_long(gb, k);

            return buf + (i << k);
        } else if (i == limit - 1) {
            buf = get_bits_long(gb, esc_len);

            return buf + 1;
        } else
            return -1;
    }
#else
    OPEN_READER(re, gb);
    UPDATE_CACHE(re, gb);
    buf = GET_CACHE(re, gb);

    log = av_log2(buf);

    av_assert2(k <= 31);

    if (log - k >= 32 - MIN_CACHE_BITS + (MIN_CACHE_BITS == 32) &&
        32 - log < limit) {
        buf >>= log - k;
        buf  += (30U - log) << k;
        LAST_SKIP_BITS(re, gb, 32 + k - log);
        CLOSE_READER(re, gb);

        return buf;
    } else {
        int i;
        for (i = 0; i + MIN_CACHE_BITS <= limit && SHOW_UBITS(re, gb, MIN_CACHE_BITS) == 0; i += MIN_CACHE_BITS) {
            if (gb->size_in_bits <= re_index) {
                CLOSE_READER(re, gb);
                return -1;
            }
            LAST_SKIP_BITS(re, gb, MIN_CACHE_BITS);
            UPDATE_CACHE(re, gb);
        }
        for (; i < limit && SHOW_UBITS(re, gb, 1) == 0; i++) {
            SKIP_BITS(re, gb, 1);
        }
        LAST_SKIP_BITS(re, gb, 1);
        UPDATE_CACHE(re, gb);

        if (i < limit - 1) {
            if (k) {
                if (k > MIN_CACHE_BITS - 1) {
                    buf = SHOW_UBITS(re, gb, 16) << (k-16);
                    LAST_SKIP_BITS(re, gb, 16);
                    UPDATE_CACHE(re, gb);
                    buf |= SHOW_UBITS(re, gb, k-16);
                    LAST_SKIP_BITS(re, gb, k-16);
                } else {
                    buf = SHOW_UBITS(re, gb, k);
                    LAST_SKIP_BITS(re, gb, k);
                }
            } else {
                buf = 0;
            }

            buf += ((SUINT)i << k);
        } else if (i == limit - 1) {
            buf = SHOW_UBITS(re, gb, esc_len);
            LAST_SKIP_BITS(re, gb, esc_len);

            buf ++;
        } else {
            buf = -1;
        }
        CLOSE_READER(re, gb);
        return buf;
    }
#endif
}