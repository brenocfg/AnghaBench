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
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int AV_RN32A (int const*) ; 
 int AV_RN64A (int const*) ; 
 int /*<<< orphan*/  AV_WN32A (int*,int) ; 
 int /*<<< orphan*/  AV_WN64A (int*,int) ; 

__attribute__((used)) static void xor_fast(const uint8_t *in1, const uint8_t *in2, uint8_t *out, int size) {
    int i, n, s;

#if HAVE_FAST_64BIT
    uint64_t v1, v2;

    n = size / sizeof (uint64_t);
    s = n * sizeof (uint64_t);

    for (i = 0; i < n; i++) {
        v1 = AV_RN64A(in1);
        v2 = AV_RN64A(in2);
        AV_WN64A(out, v1 ^ v2);
        in1 += 8;
        in2 += 8;
        out += 8;
    }
#else
    uint32_t v1, v2;

    n = size / sizeof (uint32_t);
    s = n * sizeof (uint32_t);

    for (i = 0; i < n; i++) {
        v1 = AV_RN32A(in1);
        v2 = AV_RN32A(in2);
        AV_WN32A(out, v1 ^ v2);
        in1 += 4;
        in2 += 4;
        out += 4;
    }
#endif

    n = size - s;

    for (i = 0; i < n; i++) {
        out[i] = in1[i] ^ in2[i];
    }
}