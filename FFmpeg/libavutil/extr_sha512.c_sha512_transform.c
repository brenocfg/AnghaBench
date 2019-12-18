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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 scalar_t__ Ch (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__* K512 ; 
 scalar_t__ Maj (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  R512_0 ; 
 int /*<<< orphan*/  R512_16 ; 
 scalar_t__ Sigma0_512 (scalar_t__) ; 
 scalar_t__ Sigma1_512 (scalar_t__) ; 
 scalar_t__ blk (int) ; 
 scalar_t__ blk0 (int) ; 

__attribute__((used)) static void sha512_transform(uint64_t *state, const uint8_t buffer[128])
{
    uint64_t a, b, c, d, e, f, g, h;
    uint64_t block[80];
    uint64_t T1;
    int i;

    a = state[0];
    b = state[1];
    c = state[2];
    d = state[3];
    e = state[4];
    f = state[5];
    g = state[6];
    h = state[7];
#if CONFIG_SMALL
    for (i = 0; i < 80; i++) {
        uint64_t T2;
        if (i < 16)
            T1 = blk0(i);
        else
            T1 = blk(i);
        T1 += h + Sigma1_512(e) + Ch(e, f, g) + K512[i];
        T2 = Sigma0_512(a) + Maj(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + T1;
        d = c;
        c = b;
        b = a;
        a = T1 + T2;
    }
#else

#define R512_0 \
    ROUND512_0_TO_15(a, b, c, d, e, f, g, h); \
    ROUND512_0_TO_15(h, a, b, c, d, e, f, g); \
    ROUND512_0_TO_15(g, h, a, b, c, d, e, f); \
    ROUND512_0_TO_15(f, g, h, a, b, c, d, e); \
    ROUND512_0_TO_15(e, f, g, h, a, b, c, d); \
    ROUND512_0_TO_15(d, e, f, g, h, a, b, c); \
    ROUND512_0_TO_15(c, d, e, f, g, h, a, b); \
    ROUND512_0_TO_15(b, c, d, e, f, g, h, a)

    i = 0;
    R512_0; R512_0;

#define R512_16 \
    ROUND512_16_TO_80(a, b, c, d, e, f, g, h); \
    ROUND512_16_TO_80(h, a, b, c, d, e, f, g); \
    ROUND512_16_TO_80(g, h, a, b, c, d, e, f); \
    ROUND512_16_TO_80(f, g, h, a, b, c, d, e); \
    ROUND512_16_TO_80(e, f, g, h, a, b, c, d); \
    ROUND512_16_TO_80(d, e, f, g, h, a, b, c); \
    ROUND512_16_TO_80(c, d, e, f, g, h, a, b); \
    ROUND512_16_TO_80(b, c, d, e, f, g, h, a)

    R512_16; R512_16; R512_16; R512_16;
    R512_16; R512_16; R512_16; R512_16;
#endif
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    state[4] += e;
    state[5] += f;
    state[6] += g;
    state[7] += h;
}