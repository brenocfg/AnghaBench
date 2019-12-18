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
typedef  unsigned int uint32_t ;

/* Variables and functions */
 scalar_t__ Ch (unsigned int,unsigned int,unsigned int) ; 
 scalar_t__* K256 ; 
 unsigned int Maj (unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  R256_0 ; 
 int /*<<< orphan*/  R256_16 ; 
 unsigned int Sigma0_256 (unsigned int) ; 
 scalar_t__ Sigma1_256 (unsigned int) ; 
 unsigned int blk (unsigned int) ; 
 unsigned int blk0 (unsigned int) ; 

__attribute__((used)) static void sha256_transform(uint32_t *state, const uint8_t buffer[64])
{
    unsigned int i, a, b, c, d, e, f, g, h;
    uint32_t block[64];
    uint32_t T1;

    a = state[0];
    b = state[1];
    c = state[2];
    d = state[3];
    e = state[4];
    f = state[5];
    g = state[6];
    h = state[7];
#if CONFIG_SMALL
    for (i = 0; i < 64; i++) {
        uint32_t T2;
        if (i < 16)
            T1 = blk0(i);
        else
            T1 = blk(i);
        T1 += h + Sigma1_256(e) + Ch(e, f, g) + K256[i];
        T2 = Sigma0_256(a) + Maj(a, b, c);
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

    i = 0;
#define R256_0 \
    ROUND256_0_TO_15(a, b, c, d, e, f, g, h); \
    ROUND256_0_TO_15(h, a, b, c, d, e, f, g); \
    ROUND256_0_TO_15(g, h, a, b, c, d, e, f); \
    ROUND256_0_TO_15(f, g, h, a, b, c, d, e); \
    ROUND256_0_TO_15(e, f, g, h, a, b, c, d); \
    ROUND256_0_TO_15(d, e, f, g, h, a, b, c); \
    ROUND256_0_TO_15(c, d, e, f, g, h, a, b); \
    ROUND256_0_TO_15(b, c, d, e, f, g, h, a)

    R256_0; R256_0;

#define R256_16 \
    ROUND256_16_TO_63(a, b, c, d, e, f, g, h); \
    ROUND256_16_TO_63(h, a, b, c, d, e, f, g); \
    ROUND256_16_TO_63(g, h, a, b, c, d, e, f); \
    ROUND256_16_TO_63(f, g, h, a, b, c, d, e); \
    ROUND256_16_TO_63(e, f, g, h, a, b, c, d); \
    ROUND256_16_TO_63(d, e, f, g, h, a, b, c); \
    ROUND256_16_TO_63(c, d, e, f, g, h, a, b); \
    ROUND256_16_TO_63(b, c, d, e, f, g, h, a)

    R256_16; R256_16; R256_16;
    R256_16; R256_16; R256_16;
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