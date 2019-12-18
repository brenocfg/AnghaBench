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
typedef  int uint32_t ;

/* Variables and functions */
 int AV_RN32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AV_WN32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  AV_WN64 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void fill32(uint8_t *dst, int len)
{
    uint32_t v = AV_RN32(dst - 4);

#if HAVE_FAST_64BIT
    uint64_t v2= v + ((uint64_t)v<<32);
    while (len >= 32) {
        AV_WN64(dst   , v2);
        AV_WN64(dst+ 8, v2);
        AV_WN64(dst+16, v2);
        AV_WN64(dst+24, v2);
        dst += 32;
        len -= 32;
    }
#endif

    while (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    while (len--) {
        *dst = dst[-4];
        dst++;
    }
}