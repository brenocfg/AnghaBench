#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  f3; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_5__ {int /*<<< orphan*/  f3; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_4__ {int /*<<< orphan*/  f3; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;

/* Variables and functions */
 int crc32_context ; 
 int /*<<< orphan*/  crc32_gentab () ; 
 int /*<<< orphan*/  func_1 () ; 
 int /*<<< orphan*/  g_1086 ; 
 int /*<<< orphan*/ *** g_128 ; 
 int /*<<< orphan*/  g_130 ; 
 int /*<<< orphan*/  g_132 ; 
 int /*<<< orphan*/  g_1326 ; 
 int /*<<< orphan*/  g_133 ; 
 int /*<<< orphan*/  g_1337 ; 
 int /*<<< orphan*/  g_135 ; 
 int /*<<< orphan*/  g_1413 ; 
 int /*<<< orphan*/  g_146 ; 
 int /*<<< orphan*/  g_147 ; 
 int /*<<< orphan*/  g_1585 ; 
 int /*<<< orphan*/  g_159 ; 
 int /*<<< orphan*/  g_1622 ; 
 int /*<<< orphan*/  g_1679 ; 
 int /*<<< orphan*/  g_177 ; 
 int /*<<< orphan*/  g_183 ; 
 int /*<<< orphan*/  g_1860 ; 
 int /*<<< orphan*/  g_1962 ; 
 int /*<<< orphan*/  g_20 ; 
 int /*<<< orphan*/ * g_2033 ; 
 int /*<<< orphan*/  g_204 ; 
 int /*<<< orphan*/  g_206 ; 
 TYPE_3__ g_209 ; 
 TYPE_2__ g_2193 ; 
 int /*<<< orphan*/  g_2307 ; 
 int /*<<< orphan*/  g_2497 ; 
 int /*<<< orphan*/  g_2508 ; 
 int /*<<< orphan*/  g_253 ; 
 int /*<<< orphan*/  g_254 ; 
 int /*<<< orphan*/ * g_258 ; 
 int /*<<< orphan*/  g_2648 ; 
 int /*<<< orphan*/  g_274 ; 
 int /*<<< orphan*/  g_2767 ; 
 int /*<<< orphan*/  g_2797 ; 
 int /*<<< orphan*/  g_2866 ; 
 int /*<<< orphan*/  g_2895 ; 
 int /*<<< orphan*/ * g_3176 ; 
 int /*<<< orphan*/  g_3254 ; 
 int /*<<< orphan*/  g_3261 ; 
 int /*<<< orphan*/ * g_3322 ; 
 int /*<<< orphan*/  g_3340 ; 
 int /*<<< orphan*/  g_3407 ; 
 int /*<<< orphan*/  g_3485 ; 
 int /*<<< orphan*/  g_3515 ; 
 int /*<<< orphan*/  g_3578 ; 
 int /*<<< orphan*/  g_380 ; 
 int /*<<< orphan*/  g_3815 ; 
 int /*<<< orphan*/  g_383 ; 
 int /*<<< orphan*/  g_384 ; 
 int /*<<< orphan*/  g_3847 ; 
 int /*<<< orphan*/  g_3879 ; 
 int /*<<< orphan*/  g_3880 ; 
 int /*<<< orphan*/ * g_4 ; 
 int /*<<< orphan*/  g_408 ; 
 int /*<<< orphan*/ ** g_409 ; 
 TYPE_1__ g_458 ; 
 int /*<<< orphan*/  g_471 ; 
 int /*<<< orphan*/  g_578 ; 
 int /*<<< orphan*/  g_629 ; 
 int /*<<< orphan*/ * g_67 ; 
 int /*<<< orphan*/  g_708 ; 
 int /*<<< orphan*/  g_746 ; 
 int /*<<< orphan*/ * g_75 ; 
 int /*<<< orphan*/  g_778 ; 
 int /*<<< orphan*/  g_78 ; 
 int /*<<< orphan*/  g_888 ; 
 int /*<<< orphan*/  g_91 ; 
 int /*<<< orphan*/  platform_main_begin () ; 
 int /*<<< orphan*/  platform_main_end (int,int) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  transparent_crc (int /*<<< orphan*/ ,char*,int) ; 

int main (int argc, char* argv[])
{
    int i, j, k;
    int print_hash_value = 0;
    if (argc == 2 && strcmp(argv[1], "1") == 0) print_hash_value = 1;
    platform_main_begin();
    crc32_gentab();
    func_1();
    for (i = 0; i < 5; i++)
    {
        transparent_crc(g_4[i], "g_4[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_20, "g_20", print_hash_value);
    for (i = 0; i < 7; i++)
    {
        transparent_crc(g_67[i], "g_67[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    for (i = 0; i < 3; i++)
    {
        transparent_crc(g_75[i], "g_75[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_78, "g_78", print_hash_value);
    transparent_crc(g_91, "g_91", print_hash_value);
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 4; j++)
        {
            for (k = 0; k < 3; k++)
            {
                transparent_crc(g_128[i][j][k], "g_128[i][j][k]", print_hash_value);
                if (print_hash_value) printf("index = [%d][%d][%d]\n", i, j, k);

            }
        }
    }
    transparent_crc(g_130, "g_130", print_hash_value);
    transparent_crc(g_132, "g_132", print_hash_value);
    transparent_crc(g_133, "g_133", print_hash_value);
    transparent_crc(g_135, "g_135", print_hash_value);
    transparent_crc(g_146, "g_146", print_hash_value);
    transparent_crc(g_147, "g_147", print_hash_value);
    transparent_crc(g_159, "g_159", print_hash_value);
    transparent_crc(g_177, "g_177", print_hash_value);
    transparent_crc(g_183, "g_183", print_hash_value);
    transparent_crc(g_204, "g_204", print_hash_value);
    transparent_crc(g_206, "g_206", print_hash_value);
    transparent_crc(g_209.f0, "g_209.f0", print_hash_value);
    transparent_crc(g_209.f1, "g_209.f1", print_hash_value);
    transparent_crc(g_209.f3, "g_209.f3", print_hash_value);
    transparent_crc(g_253, "g_253", print_hash_value);
    transparent_crc(g_254, "g_254", print_hash_value);
    for (i = 0; i < 8; i++)
    {
        transparent_crc(g_258[i], "g_258[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_274, "g_274", print_hash_value);
    transparent_crc(g_380, "g_380", print_hash_value);
    transparent_crc(g_383, "g_383", print_hash_value);
    transparent_crc(g_384, "g_384", print_hash_value);
    transparent_crc(g_408, "g_408", print_hash_value);
    for (i = 0; i < 1; i++)
    {
        for (j = 0; j < 4; j++)
        {
            transparent_crc(g_409[i][j], "g_409[i][j]", print_hash_value);
            if (print_hash_value) printf("index = [%d][%d]\n", i, j);

        }
    }
    transparent_crc(g_458.f0, "g_458.f0", print_hash_value);
    transparent_crc(g_458.f1, "g_458.f1", print_hash_value);
    transparent_crc(g_458.f3, "g_458.f3", print_hash_value);
    transparent_crc(g_471, "g_471", print_hash_value);
    transparent_crc(g_578, "g_578", print_hash_value);
    transparent_crc(g_629, "g_629", print_hash_value);
    transparent_crc(g_708, "g_708", print_hash_value);
    transparent_crc(g_746, "g_746", print_hash_value);
    transparent_crc(g_778, "g_778", print_hash_value);
    transparent_crc(g_888, "g_888", print_hash_value);
    transparent_crc(g_1086, "g_1086", print_hash_value);
    transparent_crc(g_1326, "g_1326", print_hash_value);
    transparent_crc(g_1337, "g_1337", print_hash_value);
    transparent_crc(g_1413, "g_1413", print_hash_value);
    transparent_crc(g_1585, "g_1585", print_hash_value);
    transparent_crc(g_1622, "g_1622", print_hash_value);
    transparent_crc(g_1679, "g_1679", print_hash_value);
    transparent_crc(g_1860, "g_1860", print_hash_value);
    transparent_crc(g_1962, "g_1962", print_hash_value);
    for (i = 0; i < 10; i++)
    {
        transparent_crc(g_2033[i], "g_2033[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_2193.f0, "g_2193.f0", print_hash_value);
    transparent_crc(g_2193.f1, "g_2193.f1", print_hash_value);
    transparent_crc(g_2193.f3, "g_2193.f3", print_hash_value);
    transparent_crc(g_2307, "g_2307", print_hash_value);
    transparent_crc(g_2497, "g_2497", print_hash_value);
    transparent_crc(g_2508, "g_2508", print_hash_value);
    transparent_crc(g_2648, "g_2648", print_hash_value);
    transparent_crc(g_2767, "g_2767", print_hash_value);
    transparent_crc(g_2797, "g_2797", print_hash_value);
    transparent_crc(g_2866, "g_2866", print_hash_value);
    transparent_crc(g_2895, "g_2895", print_hash_value);
    for (i = 0; i < 4; i++)
    {
        transparent_crc(g_3176[i], "g_3176[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_3254, "g_3254", print_hash_value);
    transparent_crc(g_3261, "g_3261", print_hash_value);
    for (i = 0; i < 7; i++)
    {
        transparent_crc(g_3322[i], "g_3322[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_3340, "g_3340", print_hash_value);
    transparent_crc(g_3407, "g_3407", print_hash_value);
    transparent_crc(g_3485, "g_3485", print_hash_value);
    transparent_crc(g_3515, "g_3515", print_hash_value);
    transparent_crc(g_3578, "g_3578", print_hash_value);
    transparent_crc(g_3815, "g_3815", print_hash_value);
    transparent_crc(g_3847, "g_3847", print_hash_value);
    transparent_crc(g_3879, "g_3879", print_hash_value);
    transparent_crc(g_3880, "g_3880", print_hash_value);
    platform_main_end(crc32_context ^ 0xFFFFFFFFUL, print_hash_value);
    return 0;
}