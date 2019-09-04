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
 int mul23 (int const,int) ; 

__attribute__((used)) static void mod64_b(int *input, int *output)
{
    static const int cos_mod[16] = {
         4199362,  4240198,  4323885,  4454708,
         4639772,  4890013,  5221943,  5660703,
         6245623,  7040975,  8158494,  9809974,
        12450076, 17261920, 28585092, 85479984
    };

    int i, k;

    for (i = 0; i < 16; i++)
        input[16 + i] = mul23(cos_mod[i], input[16 + i]);

    for (i = 0; i < 16; i++)
        output[i] = input[i] + input[16 + i];

    for (i = 16, k = 15; i < 32; i++, k--)
        output[i] = input[k] - input[16 + k];
}