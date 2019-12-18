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
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSE_READER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned int GET_CACHE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LAST_SKIP_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  OPEN_READER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned int SHOW_UBITS (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  UPDATE_CACHE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int av_log2 (unsigned int) ; 
 unsigned int get_bits_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  re ; 
 unsigned int show_bits_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits_long (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int get_ur_golomb(GetBitContext *gb, int k, int limit,
                                int esc_len)
{
    unsigned int buf;
    int log;

#if CACHED_BITSTREAM_READER
    buf = show_bits_long(gb, 32);

    log = av_log2(buf);

    if (log > 31 - limit) {
        buf >>= log - k;
        buf  += (30 - log) << k;
        skip_bits_long(gb, 32 + k - log);

        return buf;
    } else {
        skip_bits_long(gb, limit);
        buf = get_bits_long(gb, esc_len);

        return buf + limit - 1;
    }
#else
    OPEN_READER(re, gb);
    UPDATE_CACHE(re, gb);
    buf = GET_CACHE(re, gb);

    log = av_log2(buf);

    if (log > 31 - limit) {
        buf >>= log - k;
        buf  += (30U - log) << k;
        LAST_SKIP_BITS(re, gb, 32 + k - log);
        CLOSE_READER(re, gb);

        return buf;
    } else {
        LAST_SKIP_BITS(re, gb, limit);
        UPDATE_CACHE(re, gb);

        buf = SHOW_UBITS(re, gb, esc_len);

        LAST_SKIP_BITS(re, gb, esc_len);
        CLOSE_READER(re, gb);

        return buf + limit - 1;
    }
#endif
}