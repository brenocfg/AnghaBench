#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  f4; int /*<<< orphan*/  f3; int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_9__ {int /*<<< orphan*/  f4; int /*<<< orphan*/  f3; int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_8__ {int /*<<< orphan*/  f4; int /*<<< orphan*/  f3; int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_7__ {int /*<<< orphan*/  f4; int /*<<< orphan*/  f3; int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_6__ {int /*<<< orphan*/  f4; int /*<<< orphan*/  f3; int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;

/* Variables and functions */
 int crc32_context ; 
 int /*<<< orphan*/  crc32_gentab () ; 
 int /*<<< orphan*/  func_1 () ; 
 int /*<<< orphan*/  g_1042 ; 
 int /*<<< orphan*/  g_1058 ; 
 int /*<<< orphan*/  g_11 ; 
 int /*<<< orphan*/ * g_1138 ; 
 int /*<<< orphan*/  g_12 ; 
 int /*<<< orphan*/  g_1225 ; 
 int /*<<< orphan*/  g_1239 ; 
 int /*<<< orphan*/ * g_1257 ; 
 int /*<<< orphan*/  g_1261 ; 
 int /*<<< orphan*/ * g_1402 ; 
 int /*<<< orphan*/  g_1436 ; 
 int /*<<< orphan*/  g_15 ; 
 int /*<<< orphan*/  g_150 ; 
 int /*<<< orphan*/ ** g_156 ; 
 int /*<<< orphan*/  g_1682 ; 
 int /*<<< orphan*/ *** g_1695 ; 
 int /*<<< orphan*/  g_20 ; 
 int /*<<< orphan*/  g_2022 ; 
 int /*<<< orphan*/  g_2037 ; 
 int /*<<< orphan*/  g_2052 ; 
 int /*<<< orphan*/  g_213 ; 
 int /*<<< orphan*/ ** g_278 ; 
 int /*<<< orphan*/  g_294 ; 
 int /*<<< orphan*/ * g_3 ; 
 int /*<<< orphan*/  g_353 ; 
 int /*<<< orphan*/  g_356 ; 
 int /*<<< orphan*/  g_357 ; 
 int /*<<< orphan*/ * g_359 ; 
 int /*<<< orphan*/  g_428 ; 
 TYPE_5__ g_433 ; 
 int /*<<< orphan*/  g_489 ; 
 int /*<<< orphan*/  g_5 ; 
 int /*<<< orphan*/  g_504 ; 
 int /*<<< orphan*/  g_518 ; 
 int /*<<< orphan*/ ** g_544 ; 
 TYPE_4__ g_576 ; 
 int /*<<< orphan*/  g_584 ; 
 int /*<<< orphan*/ * g_6 ; 
 TYPE_3__ g_68 ; 
 int /*<<< orphan*/  g_698 ; 
 int /*<<< orphan*/  g_760 ; 
 int /*<<< orphan*/  g_83 ; 
 int /*<<< orphan*/ *** g_857 ; 
 int /*<<< orphan*/  g_90 ; 
 TYPE_2__* g_905 ; 
 TYPE_1__*** g_92 ; 
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
    for (i = 0; i < 6; i++)
    {
        transparent_crc(g_3[i], "g_3[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_5, "g_5", print_hash_value);
    for (i = 0; i < 10; i++)
    {
        transparent_crc(g_6[i], "g_6[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_11, "g_11", print_hash_value);
    transparent_crc(g_12, "g_12", print_hash_value);
    transparent_crc(g_15, "g_15", print_hash_value);
    transparent_crc(g_20, "g_20", print_hash_value);
    transparent_crc(g_68.f0, "g_68.f0", print_hash_value);
    transparent_crc(g_68.f1, "g_68.f1", print_hash_value);
    transparent_crc(g_68.f2, "g_68.f2", print_hash_value);
    transparent_crc(g_68.f3, "g_68.f3", print_hash_value);
    transparent_crc(g_68.f4, "g_68.f4", print_hash_value);
    transparent_crc(g_83, "g_83", print_hash_value);
    transparent_crc(g_90, "g_90", print_hash_value);
    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 4; j++)
        {
            for (k = 0; k < 9; k++)
            {
                transparent_crc(g_92[i][j][k].f0, "g_92[i][j][k].f0", print_hash_value);
                transparent_crc(g_92[i][j][k].f1, "g_92[i][j][k].f1", print_hash_value);
                transparent_crc(g_92[i][j][k].f2, "g_92[i][j][k].f2", print_hash_value);
                transparent_crc(g_92[i][j][k].f3, "g_92[i][j][k].f3", print_hash_value);
                transparent_crc(g_92[i][j][k].f4, "g_92[i][j][k].f4", print_hash_value);
                if (print_hash_value) printf("index = [%d][%d][%d]\n", i, j, k);

            }
        }
    }
    transparent_crc(g_97, "g_97", print_hash_value);
    transparent_crc(g_150, "g_150", print_hash_value);
    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 8; j++)
        {
            transparent_crc(g_156[i][j], "g_156[i][j]", print_hash_value);
            if (print_hash_value) printf("index = [%d][%d]\n", i, j);

        }
    }
    transparent_crc(g_213, "g_213", print_hash_value);
    for (i = 0; i < 1; i++)
    {
        for (j = 0; j < 4; j++)
        {
            transparent_crc(g_278[i][j], "g_278[i][j]", print_hash_value);
            if (print_hash_value) printf("index = [%d][%d]\n", i, j);

        }
    }
    transparent_crc(g_294, "g_294", print_hash_value);
    transparent_crc(g_353, "g_353", print_hash_value);
    transparent_crc(g_356, "g_356", print_hash_value);
    transparent_crc(g_357, "g_357", print_hash_value);
    for (i = 0; i < 4; i++)
    {
        transparent_crc(g_359[i], "g_359[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_428, "g_428", print_hash_value);
    transparent_crc(g_433.f0, "g_433.f0", print_hash_value);
    transparent_crc(g_433.f1, "g_433.f1", print_hash_value);
    transparent_crc(g_433.f2, "g_433.f2", print_hash_value);
    transparent_crc(g_433.f3, "g_433.f3", print_hash_value);
    transparent_crc(g_433.f4, "g_433.f4", print_hash_value);
    transparent_crc(g_489, "g_489", print_hash_value);
    transparent_crc(g_504, "g_504", print_hash_value);
    transparent_crc(g_518, "g_518", print_hash_value);
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 4; j++)
        {
            transparent_crc(g_544[i][j], "g_544[i][j]", print_hash_value);
            if (print_hash_value) printf("index = [%d][%d]\n", i, j);

        }
    }
    transparent_crc(g_576.f0, "g_576.f0", print_hash_value);
    transparent_crc(g_576.f1, "g_576.f1", print_hash_value);
    transparent_crc(g_576.f2, "g_576.f2", print_hash_value);
    transparent_crc(g_576.f3, "g_576.f3", print_hash_value);
    transparent_crc(g_576.f4, "g_576.f4", print_hash_value);
    transparent_crc(g_584, "g_584", print_hash_value);
    transparent_crc(g_698, "g_698", print_hash_value);
    transparent_crc(g_760, "g_760", print_hash_value);
    for (i = 0; i < 1; i++)
    {
        for (j = 0; j < 9; j++)
        {
            for (k = 0; k < 4; k++)
            {
                transparent_crc(g_857[i][j][k], "g_857[i][j][k]", print_hash_value);
                if (print_hash_value) printf("index = [%d][%d][%d]\n", i, j, k);

            }
        }
    }
    for (i = 0; i < 7; i++)
    {
        transparent_crc(g_905[i].f0, "g_905[i].f0", print_hash_value);
        transparent_crc(g_905[i].f1, "g_905[i].f1", print_hash_value);
        transparent_crc(g_905[i].f2, "g_905[i].f2", print_hash_value);
        transparent_crc(g_905[i].f3, "g_905[i].f3", print_hash_value);
        transparent_crc(g_905[i].f4, "g_905[i].f4", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_1042, "g_1042", print_hash_value);
    transparent_crc(g_1058, "g_1058", print_hash_value);
    for (i = 0; i < 10; i++)
    {
        transparent_crc(g_1138[i], "g_1138[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_1225, "g_1225", print_hash_value);
    transparent_crc(g_1239, "g_1239", print_hash_value);
    for (i = 0; i < 8; i++)
    {
        transparent_crc(g_1257[i], "g_1257[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_1261, "g_1261", print_hash_value);
    for (i = 0; i < 5; i++)
    {
        transparent_crc(g_1402[i], "g_1402[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_1436, "g_1436", print_hash_value);
    transparent_crc(g_1682, "g_1682", print_hash_value);
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 5; j++)
        {
            for (k = 0; k < 9; k++)
            {
                transparent_crc(g_1695[i][j][k], "g_1695[i][j][k]", print_hash_value);
                if (print_hash_value) printf("index = [%d][%d][%d]\n", i, j, k);

            }
        }
    }
    transparent_crc(g_2022, "g_2022", print_hash_value);
    transparent_crc(g_2037, "g_2037", print_hash_value);
    transparent_crc(g_2052, "g_2052", print_hash_value);
    platform_main_end(crc32_context ^ 0xFFFFFFFFUL, print_hash_value);
    return 0;
}