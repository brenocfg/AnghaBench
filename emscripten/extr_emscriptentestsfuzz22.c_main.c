#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_24__ {int /*<<< orphan*/  f3; int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_23__ {int /*<<< orphan*/  f0; } ;
struct TYPE_22__ {int /*<<< orphan*/  f9; int /*<<< orphan*/  f8; int /*<<< orphan*/  f7; int /*<<< orphan*/  f6; int /*<<< orphan*/  f5; int /*<<< orphan*/  f4; int /*<<< orphan*/  f3; int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_21__ {int /*<<< orphan*/  f3; int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_20__ {int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_19__ {int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_18__ {int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_17__ {int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_16__ {int /*<<< orphan*/  f3; int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_15__ {int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_14__ {int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_13__ {int /*<<< orphan*/  f9; int /*<<< orphan*/  f8; int /*<<< orphan*/  f7; int /*<<< orphan*/  f6; int /*<<< orphan*/  f5; int /*<<< orphan*/  f4; int /*<<< orphan*/  f3; int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;

/* Variables and functions */
 int crc32_context ; 
 int /*<<< orphan*/  crc32_gentab () ; 
 int /*<<< orphan*/  func_1 () ; 
 int /*<<< orphan*/  g_100 ; 
 int /*<<< orphan*/  g_104 ; 
 int /*<<< orphan*/ * g_106 ; 
 int /*<<< orphan*/  g_118 ; 
 int /*<<< orphan*/ *** g_14 ; 
 TYPE_12__ g_143 ; 
 int /*<<< orphan*/ * g_17 ; 
 int /*<<< orphan*/  g_18 ; 
 int /*<<< orphan*/  g_189 ; 
 TYPE_11__ g_213 ; 
 int /*<<< orphan*/ * g_226 ; 
 TYPE_10__ g_231 ; 
 TYPE_9__ g_249 ; 
 TYPE_8__* g_252 ; 
 int /*<<< orphan*/  g_287 ; 
 TYPE_7__ g_313 ; 
 int /*<<< orphan*/  g_334 ; 
 int /*<<< orphan*/  g_339 ; 
 int /*<<< orphan*/  g_342 ; 
 int /*<<< orphan*/  g_348 ; 
 int /*<<< orphan*/  g_359 ; 
 int /*<<< orphan*/  g_362 ; 
 TYPE_6__ g_385 ; 
 int /*<<< orphan*/  g_4 ; 
 int /*<<< orphan*/  g_440 ; 
 int /*<<< orphan*/  g_476 ; 
 int /*<<< orphan*/ *** g_510 ; 
 int /*<<< orphan*/  g_538 ; 
 int /*<<< orphan*/  g_569 ; 
 TYPE_5__ g_584 ; 
 TYPE_4__ g_586 ; 
 TYPE_3__ g_588 ; 
 int /*<<< orphan*/ * g_629 ; 
 int /*<<< orphan*/  g_677 ; 
 int /*<<< orphan*/  g_689 ; 
 int /*<<< orphan*/  g_70 ; 
 int /*<<< orphan*/  g_723 ; 
 int /*<<< orphan*/  g_733 ; 
 TYPE_2__ g_736 ; 
 int /*<<< orphan*/  g_79 ; 
 int /*<<< orphan*/ * g_846 ; 
 int /*<<< orphan*/  g_861 ; 
 TYPE_1__ g_900 ; 
 int /*<<< orphan*/  g_97 ; 
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
    transparent_crc(g_4, "g_4", print_hash_value);
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            for (k = 0; k < 1; k++)
            {
                transparent_crc(g_14[i][j][k], "g_14[i][j][k]", print_hash_value);
                if (print_hash_value) printf("index = [%d][%d][%d]\n", i, j, k);

            }
        }
    }
    for (i = 0; i < 4; i++)
    {
        transparent_crc(g_17[i], "g_17[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_18, "g_18", print_hash_value);
    transparent_crc(g_70, "g_70", print_hash_value);
    transparent_crc(g_79, "g_79", print_hash_value);
    transparent_crc(g_97, "g_97", print_hash_value);
    transparent_crc(g_100, "g_100", print_hash_value);
    transparent_crc(g_104, "g_104", print_hash_value);
    for (i = 0; i < 4; i++)
    {
        transparent_crc(g_106[i], "g_106[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_118, "g_118", print_hash_value);
    transparent_crc(g_143.f0, "g_143.f0", print_hash_value);
    transparent_crc(g_143.f1, "g_143.f1", print_hash_value);
    transparent_crc(g_143.f2, "g_143.f2", print_hash_value);
    transparent_crc(g_189, "g_189", print_hash_value);
    transparent_crc(g_213.f0, "g_213.f0", print_hash_value);
    transparent_crc(g_213.f1, "g_213.f1", print_hash_value);
    transparent_crc(g_213.f2, "g_213.f2", print_hash_value);
    for (i = 0; i < 6; i++)
    {
        transparent_crc(g_226[i], "g_226[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_231.f0, "g_231.f0", print_hash_value);
    transparent_crc(g_231.f1, "g_231.f1", print_hash_value);
    transparent_crc(g_231.f2, "g_231.f2", print_hash_value);
    transparent_crc(g_231.f3, "g_231.f3", print_hash_value);
    transparent_crc(g_231.f4, "g_231.f4", print_hash_value);
    transparent_crc(g_231.f5, "g_231.f5", print_hash_value);
    transparent_crc(g_231.f6, "g_231.f6", print_hash_value);
    transparent_crc(g_231.f7, "g_231.f7", print_hash_value);
    transparent_crc(g_231.f8, "g_231.f8", print_hash_value);
    transparent_crc(g_231.f9, "g_231.f9", print_hash_value);
    transparent_crc(g_249.f0, "g_249.f0", print_hash_value);
    transparent_crc(g_249.f1, "g_249.f1", print_hash_value);
    transparent_crc(g_249.f2, "g_249.f2", print_hash_value);
    transparent_crc(g_249.f3, "g_249.f3", print_hash_value);
    for (i = 0; i < 2; i++)
    {
        transparent_crc(g_252[i].f0, "g_252[i].f0", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_287, "g_287", print_hash_value);
    transparent_crc(g_313.f0, "g_313.f0", print_hash_value);
    transparent_crc(g_313.f1, "g_313.f1", print_hash_value);
    transparent_crc(g_313.f2, "g_313.f2", print_hash_value);
    transparent_crc(g_313.f3, "g_313.f3", print_hash_value);
    transparent_crc(g_313.f4, "g_313.f4", print_hash_value);
    transparent_crc(g_313.f5, "g_313.f5", print_hash_value);
    transparent_crc(g_313.f6, "g_313.f6", print_hash_value);
    transparent_crc(g_313.f7, "g_313.f7", print_hash_value);
    transparent_crc(g_313.f8, "g_313.f8", print_hash_value);
    transparent_crc(g_313.f9, "g_313.f9", print_hash_value);
    transparent_crc(g_334, "g_334", print_hash_value);
    transparent_crc(g_339, "g_339", print_hash_value);
    transparent_crc(g_342, "g_342", print_hash_value);
    transparent_crc(g_348, "g_348", print_hash_value);
    transparent_crc(g_359, "g_359", print_hash_value);
    transparent_crc(g_362, "g_362", print_hash_value);
    transparent_crc(g_385.f0, "g_385.f0", print_hash_value);
    transparent_crc(g_385.f1, "g_385.f1", print_hash_value);
    transparent_crc(g_385.f2, "g_385.f2", print_hash_value);
    transparent_crc(g_385.f3, "g_385.f3", print_hash_value);
    transparent_crc(g_440, "g_440", print_hash_value);
    transparent_crc(g_476, "g_476", print_hash_value);
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 7; j++)
        {
            for (k = 0; k < 1; k++)
            {
                transparent_crc(g_510[i][j][k], "g_510[i][j][k]", print_hash_value);
                if (print_hash_value) printf("index = [%d][%d][%d]\n", i, j, k);

            }
        }
    }
    transparent_crc(g_538, "g_538", print_hash_value);
    transparent_crc(g_569, "g_569", print_hash_value);
    transparent_crc(g_584.f0, "g_584.f0", print_hash_value);
    transparent_crc(g_584.f1, "g_584.f1", print_hash_value);
    transparent_crc(g_584.f2, "g_584.f2", print_hash_value);
    transparent_crc(g_586.f0, "g_586.f0", print_hash_value);
    transparent_crc(g_586.f1, "g_586.f1", print_hash_value);
    transparent_crc(g_586.f2, "g_586.f2", print_hash_value);
    transparent_crc(g_588.f0, "g_588.f0", print_hash_value);
    transparent_crc(g_588.f1, "g_588.f1", print_hash_value);
    transparent_crc(g_588.f2, "g_588.f2", print_hash_value);
    for (i = 0; i < 9; i++)
    {
        transparent_crc(g_629[i], "g_629[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_677, "g_677", print_hash_value);
    transparent_crc(g_689, "g_689", print_hash_value);
    transparent_crc(g_723, "g_723", print_hash_value);
    transparent_crc(g_733, "g_733", print_hash_value);
    transparent_crc(g_736.f0, "g_736.f0", print_hash_value);
    transparent_crc(g_736.f1, "g_736.f1", print_hash_value);
    transparent_crc(g_736.f2, "g_736.f2", print_hash_value);
    for (i = 0; i < 3; i++)
    {
        transparent_crc(g_846[i], "g_846[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_861, "g_861", print_hash_value);
    transparent_crc(g_900.f0, "g_900.f0", print_hash_value);
    transparent_crc(g_900.f1, "g_900.f1", print_hash_value);
    transparent_crc(g_900.f2, "g_900.f2", print_hash_value);
    transparent_crc(g_900.f3, "g_900.f3", print_hash_value);
    platform_main_end(crc32_context ^ 0xFFFFFFFFUL, print_hash_value);
    return 0;
}