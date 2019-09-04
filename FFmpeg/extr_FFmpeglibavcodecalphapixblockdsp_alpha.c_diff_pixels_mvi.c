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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int cmpbge (int,int) ; 
 int ldq (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stq (int,int /*<<< orphan*/ *) ; 
 int unpkbw (int) ; 
 int zap (int,int) ; 

__attribute__((used)) static void diff_pixels_mvi(int16_t *block, const uint8_t *s1, const uint8_t *s2,
                            ptrdiff_t stride)
{
    int h = 8;
    uint64_t mask = 0x4040;

    mask |= mask << 16;
    mask |= mask << 32;
    do {
        uint64_t x, y, c, d, a;
        uint64_t signs;

        x = ldq(s1);
        y = ldq(s2);
        c = cmpbge(x, y);
        d = x - y;
        a = zap(mask, c);       /* We use 0x4040404040404040 here...  */
        d += 4 * a;             /* ...so we can use s4addq here.      */
        signs = zap(-1, c);

        stq(unpkbw(d)       | (unpkbw(signs)       << 8), block);
        stq(unpkbw(d >> 32) | (unpkbw(signs >> 32) << 8), block + 4);

        s1 += stride;
        s2 += stride;
        block += 8;
    } while (--h);
}