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
 int /*<<< orphan*/  LAST_SKIP_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPEN_READER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UPDATE_CACHE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ff_golomb_vlc_len ; 
 int* ff_ue_golomb_vlc_code ; 
 int /*<<< orphan*/  re ; 
 unsigned int show_bits_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits_long (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int get_ue_golomb_31(GetBitContext *gb)
{
    unsigned int buf;

#if CACHED_BITSTREAM_READER
    buf = show_bits_long(gb, 32);

    buf >>= 32 - 9;
    skip_bits_long(gb, ff_golomb_vlc_len[buf]);
#else

    OPEN_READER(re, gb);
    UPDATE_CACHE(re, gb);
    buf = GET_CACHE(re, gb);

    buf >>= 32 - 9;
    LAST_SKIP_BITS(re, gb, ff_golomb_vlc_len[buf]);
    CLOSE_READER(re, gb);
#endif

    return ff_ue_golomb_vlc_code[buf];
}