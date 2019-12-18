#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int bits_left; } ;
typedef  TYPE_1__ GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSE_READER (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  LAST_SKIP_BITS (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  OPEN_READER (int /*<<< orphan*/ ,TYPE_1__*) ; 
 unsigned int SHOW_UBITS (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 unsigned int UINT64_C (int) ; 
 int /*<<< orphan*/  UPDATE_CACHE (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  av_assert2 (int) ; 
 unsigned int get_val (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  re ; 
 int /*<<< orphan*/  refill_32 (TYPE_1__*,int) ; 

__attribute__((used)) static inline unsigned int get_bits(GetBitContext *s, int n)
{
    register unsigned int tmp;
#if CACHED_BITSTREAM_READER

    av_assert2(n>0 && n<=32);
    if (n > s->bits_left) {
#ifdef BITSTREAM_READER_LE
        refill_32(s, 1);
#else
        refill_32(s, 0);
#endif
        if (s->bits_left < 32)
            s->bits_left = n;
    }

#ifdef BITSTREAM_READER_LE
    tmp = get_val(s, n, 1);
#else
    tmp = get_val(s, n, 0);
#endif
#else
    OPEN_READER(re, s);
    av_assert2(n>0 && n<=25);
    UPDATE_CACHE(re, s);
    tmp = SHOW_UBITS(re, s, n);
    LAST_SKIP_BITS(re, s, n);
    CLOSE_READER(re, s);
#endif
    av_assert2(tmp < UINT64_C(1) << n);
    return tmp;
}