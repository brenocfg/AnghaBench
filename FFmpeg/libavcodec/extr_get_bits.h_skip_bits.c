#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int bits_left; unsigned int index; scalar_t__ cache; } ;
typedef  TYPE_1__ GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSE_READER (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  LAST_SKIP_BITS (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  OPEN_READER (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  re ; 
 int /*<<< orphan*/  refill_64 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  skip_remaining (TYPE_1__*,int) ; 

__attribute__((used)) static inline void skip_bits(GetBitContext *s, int n)
{
#if CACHED_BITSTREAM_READER
    if (n < s->bits_left)
        skip_remaining(s, n);
    else {
        n -= s->bits_left;
        s->cache = 0;
        s->bits_left = 0;

        if (n >= 64) {
            unsigned skip = (n / 8) * 8;

            n -= skip;
            s->index += skip;
        }
#ifdef BITSTREAM_READER_LE
        refill_64(s, 1);
#else
        refill_64(s, 0);
#endif
        if (n)
            skip_remaining(s, n);
    }
#else
    OPEN_READER(re, s);
    LAST_SKIP_BITS(re, s, n);
    CLOSE_READER(re, s);
#endif
}