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

/* Variables and functions */
 int mul23 (int const,int const) ; 

__attribute__((used)) static void mod64_a(const int *input, int *output)
{
    static const int cos_mod[32] = {
          4195568,   4205700,   4226086,    4256977,
          4298755,   4351949,   4417251,    4495537,
          4587901,   4695690,   4820557,    4964534,
          5130115,   5320382,   5539164,    5791261,
         -6082752,  -6421430,  -6817439,   -7284203,
         -7839855,  -8509474,  -9328732,  -10350140,
        -11654242, -13371208, -15725922,  -19143224,
        -24533560, -34264200, -57015280, -170908480
    };

    int i, k;

    for (i = 0; i < 16; i++)
        output[i] = mul23(cos_mod[i], input[i] + input[16 + i]);

    for (i = 16, k = 15; i < 32; i++, k--)
        output[i] = mul23(cos_mod[i], input[k] - input[16 + k]);
}