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

__attribute__((used)) static void mod64_c(const int *input, int *output)
{
    static const int cos_mod[64] = {
          741511,    741958,    742853,    744199,
          746001,    748262,    750992,    754197,
          757888,    762077,    766777,    772003,
          777772,    784105,    791021,    798546,
          806707,    815532,    825054,    835311,
          846342,    858193,    870912,    884554,
          899181,    914860,    931667,    949686,
          969011,    989747,   1012012,   1035941,
        -1061684,  -1089412,  -1119320,  -1151629,
        -1186595,  -1224511,  -1265719,  -1310613,
        -1359657,  -1413400,  -1472490,  -1537703,
        -1609974,  -1690442,  -1780506,  -1881904,
        -1996824,  -2128058,  -2279225,  -2455101,
        -2662128,  -2909200,  -3208956,  -3579983,
        -4050785,  -4667404,  -5509372,  -6726913,
        -8641940, -12091426, -20144284, -60420720
    };

    int i, k;

    for (i = 0; i < 32; i++)
        output[i] = mul23(cos_mod[i], input[i] + input[32 + i]);

    for (i = 32, k = 31; i < 64; i++, k--)
        output[i] = mul23(cos_mod[i], input[k] - input[32 + k]);
}