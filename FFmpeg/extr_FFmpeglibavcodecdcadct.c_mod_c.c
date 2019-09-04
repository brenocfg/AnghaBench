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

__attribute__((used)) static void mod_c(const int *input, int *output)
{
    static const int cos_mod[32] = {
         1048892,  1051425,   1056522,   1064244,
         1074689,  1087987,   1104313,   1123884,
         1146975,  1173922,   1205139,   1241133,
         1282529,  1330095,   1384791,   1447815,
        -1520688, -1605358,  -1704360,  -1821051,
        -1959964, -2127368,  -2332183,  -2587535,
        -2913561, -3342802,  -3931480,  -4785806,
        -6133390, -8566050, -14253820, -42727120
    };

    int i, k;

    for (i = 0; i < 16; i++)
        output[i] = mul23(cos_mod[i], input[i] + input[16 + i]);

    for (i = 16, k = 15; i < 32; i++, k--)
        output[i] = mul23(cos_mod[i], input[k] - input[16 + k]);
}