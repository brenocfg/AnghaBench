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
 int /*<<< orphan*/  UPDATE_CACHE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int av_log2 (unsigned int) ; 
 int* ff_golomb_vlc_len ; 
 int* ff_se_golomb_vlc_code ; 
 int /*<<< orphan*/  re ; 
 unsigned int show_bits_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits_long (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int get_se_golomb(GetBitContext *gb)
{
    unsigned int buf;

#if CACHED_BITSTREAM_READER
    buf = show_bits_long(gb, 32);

    if (buf >= (1 << 27)) {
        buf >>= 32 - 9;
        skip_bits_long(gb, ff_golomb_vlc_len[buf]);

        return ff_se_golomb_vlc_code[buf];
    } else {
        int log = 2 * av_log2(buf) - 31;
        buf >>= log;

        skip_bits_long(gb, 32 - log);

        if (buf & 1)
            buf = -(buf >> 1);
        else
            buf = (buf >> 1);

        return buf;
    }
#else
    OPEN_READER(re, gb);
    UPDATE_CACHE(re, gb);
    buf = GET_CACHE(re, gb);

    if (buf >= (1 << 27)) {
        buf >>= 32 - 9;
        LAST_SKIP_BITS(re, gb, ff_golomb_vlc_len[buf]);
        CLOSE_READER(re, gb);

        return ff_se_golomb_vlc_code[buf];
    } else {
        int log = av_log2(buf), sign;
        LAST_SKIP_BITS(re, gb, 31 - log);
        UPDATE_CACHE(re, gb);
        buf = GET_CACHE(re, gb);

        buf >>= log;

        LAST_SKIP_BITS(re, gb, 32 - log);
        CLOSE_READER(re, gb);

        sign = -(buf & 1);
        buf  = ((buf >> 1) ^ sign) - sign;

        return buf;
    }
#endif
}