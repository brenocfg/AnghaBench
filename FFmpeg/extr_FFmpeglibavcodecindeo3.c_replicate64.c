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
typedef  int uint64_t ;

/* Variables and functions */

__attribute__((used)) static inline uint64_t replicate64(uint64_t a) {
#if HAVE_BIGENDIAN
    a &= 0xFF00FF00FF00FF00ULL;
    a |= a >> 8;
#else
    a &= 0x00FF00FF00FF00FFULL;
    a |= a << 8;
#endif
    return a;
}