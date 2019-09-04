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
 int ldq (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unpkbw (int) ; 

__attribute__((used)) static void get_pixels_mvi(int16_t *restrict block,
                           const uint8_t *restrict pixels, ptrdiff_t stride)
{
    int h = 8;

    do {
        uint64_t p;

        p = ldq(pixels);
        stq(unpkbw(p),       block);
        stq(unpkbw(p >> 32), block + 4);

        pixels += stride;
        block += 8;
    } while (--h);
}