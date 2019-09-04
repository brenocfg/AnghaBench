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
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ abs (int const) ; 
 int clip23 (int) ; 
 int /*<<< orphan*/  clp_v (int*,int) ; 
 int /*<<< orphan*/  dct_a (int*,int*) ; 
 int /*<<< orphan*/  dct_b (int*,int*) ; 
 int /*<<< orphan*/  mod64_a (int*,int*) ; 
 int /*<<< orphan*/  mod64_b (int*,int*) ; 
 int /*<<< orphan*/  mod64_c (int*,int*) ; 
 int /*<<< orphan*/  mod_a (int*,int*) ; 
 int /*<<< orphan*/  mod_b (int*,int*) ; 
 int /*<<< orphan*/  sum_a (int*,int*,int) ; 
 int /*<<< orphan*/  sum_b (int*,int*,int) ; 
 int /*<<< orphan*/  sum_c (int*,int*,int) ; 
 int /*<<< orphan*/  sum_d (int*,int*,int) ; 

__attribute__((used)) static void imdct_half_64(int32_t *output, const int32_t *input)
{
    int buf_a[64], buf_b[64];
    int i, k, mag, shift, round;

    mag = 0;
    for (i = 0; i < 64; i++)
        mag += abs(input[i]);

    shift = mag > 0x400000 ? 2 : 0;
    round = shift > 0 ? 1 << (shift - 1) : 0;

    for (i = 0; i < 64; i++)
        buf_a[i] = (input[i] + round) >> shift;

    sum_a(buf_a, buf_b +  0, 32);
    sum_b(buf_a, buf_b + 32, 32);
    clp_v(buf_b, 64);

    sum_a(buf_b +  0, buf_a +  0, 16);
    sum_b(buf_b +  0, buf_a + 16, 16);
    sum_c(buf_b + 32, buf_a + 32, 16);
    sum_d(buf_b + 32, buf_a + 48, 16);
    clp_v(buf_a, 64);

    sum_a(buf_a +  0, buf_b +  0, 8);
    sum_b(buf_a +  0, buf_b +  8, 8);
    sum_c(buf_a + 16, buf_b + 16, 8);
    sum_d(buf_a + 16, buf_b + 24, 8);
    sum_c(buf_a + 32, buf_b + 32, 8);
    sum_d(buf_a + 32, buf_b + 40, 8);
    sum_c(buf_a + 48, buf_b + 48, 8);
    sum_d(buf_a + 48, buf_b + 56, 8);
    clp_v(buf_b, 64);

    dct_a(buf_b +  0, buf_a +  0);
    dct_b(buf_b +  8, buf_a +  8);
    dct_b(buf_b + 16, buf_a + 16);
    dct_b(buf_b + 24, buf_a + 24);
    dct_b(buf_b + 32, buf_a + 32);
    dct_b(buf_b + 40, buf_a + 40);
    dct_b(buf_b + 48, buf_a + 48);
    dct_b(buf_b + 56, buf_a + 56);
    clp_v(buf_a, 64);

    mod_a(buf_a +  0, buf_b +  0);
    mod_b(buf_a + 16, buf_b + 16);
    mod_b(buf_a + 32, buf_b + 32);
    mod_b(buf_a + 48, buf_b + 48);
    clp_v(buf_b, 64);

    mod64_a(buf_b +  0, buf_a +  0);
    mod64_b(buf_b + 32, buf_a + 32);
    clp_v(buf_a, 64);

    mod64_c(buf_a, buf_b);

    for (i = 0; i < 64; i++)
        buf_b[i] = clip23(buf_b[i] * (1 << shift));

    for (i = 0, k = 63; i < 32; i++, k--) {
        output[     i] = clip23(buf_b[i] - buf_b[k]);
        output[32 + i] = clip23(buf_b[i] + buf_b[k]);
    }
}