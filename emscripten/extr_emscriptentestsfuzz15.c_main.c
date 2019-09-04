#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  f4; int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_17__ {int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_16__ {int /*<<< orphan*/  f4; int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_15__ {int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_14__ {int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_13__ {int /*<<< orphan*/  f1; } ;
struct TYPE_12__ {int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_11__ {int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_10__ {int /*<<< orphan*/  f4; int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;

/* Variables and functions */
 int crc32_context ; 
 int /*<<< orphan*/  crc32_gentab () ; 
 int /*<<< orphan*/  func_1 () ; 
 TYPE_9__* g_10 ; 
 int /*<<< orphan*/  g_1007 ; 
 int /*<<< orphan*/  g_101 ; 
 int /*<<< orphan*/ ** g_111 ; 
 int /*<<< orphan*/  g_1178 ; 
 int /*<<< orphan*/ ** g_1198 ; 
 int /*<<< orphan*/  g_1232 ; 
 int /*<<< orphan*/ *** g_1399 ; 
 int /*<<< orphan*/  g_147 ; 
 int /*<<< orphan*/  g_149 ; 
 TYPE_8__* g_1574 ; 
 int /*<<< orphan*/  g_1582 ; 
 int /*<<< orphan*/  g_1693 ; 
 int /*<<< orphan*/  g_1695 ; 
 int /*<<< orphan*/  g_1743 ; 
 int /*<<< orphan*/  g_1771 ; 
 int /*<<< orphan*/ *** g_1864 ; 
 int /*<<< orphan*/  g_2 ; 
 int /*<<< orphan*/  g_2120 ; 
 TYPE_7__ g_223 ; 
 TYPE_6__ g_226 ; 
 TYPE_5__*** g_229 ; 
 TYPE_4__*** g_231 ; 
 int /*<<< orphan*/  g_245 ; 
 TYPE_3__ g_255 ; 
 int /*<<< orphan*/  g_319 ; 
 int /*<<< orphan*/  g_375 ; 
 TYPE_2__*** g_428 ; 
 int /*<<< orphan*/  g_444 ; 
 int /*<<< orphan*/  g_479 ; 
 int /*<<< orphan*/  g_49 ; 
 int /*<<< orphan*/  g_507 ; 
 int /*<<< orphan*/ * g_53 ; 
 int /*<<< orphan*/  g_627 ; 
 int /*<<< orphan*/  g_706 ; 
 int /*<<< orphan*/  g_75 ; 
 TYPE_1__ g_814 ; 
 int /*<<< orphan*/  g_89 ; 
 int /*<<< orphan*/  g_92 ; 
 int /*<<< orphan*/  g_93 ; 
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
    transparent_crc(g_2, "g_2", print_hash_value);
    for (i = 0; i < 10; i++)
    {
        transparent_crc(g_10[i].f0, "g_10[i].f0", print_hash_value);
        transparent_crc(g_10[i].f1, "g_10[i].f1", print_hash_value);
        transparent_crc(g_10[i].f2, "g_10[i].f2", print_hash_value);
        transparent_crc(g_10[i].f4, "g_10[i].f4", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_49, "g_49", print_hash_value);
    for (i = 0; i < 6; i++)
    {
        transparent_crc(g_53[i], "g_53[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_75, "g_75", print_hash_value);
    transparent_crc(g_89, "g_89", print_hash_value);
    transparent_crc(g_92, "g_92", print_hash_value);
    transparent_crc(g_93, "g_93", print_hash_value);
    transparent_crc(g_101, "g_101", print_hash_value);
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            transparent_crc(g_111[i][j], "g_111[i][j]", print_hash_value);
            if (print_hash_value) printf("index = [%d][%d]\n", i, j);

        }
    }
    transparent_crc(g_147, "g_147", print_hash_value);
    transparent_crc(g_149, "g_149", print_hash_value);
    transparent_crc(g_223.f0, "g_223.f0", print_hash_value);
    transparent_crc(g_223.f1, "g_223.f1", print_hash_value);
    transparent_crc(g_223.f2, "g_223.f2", print_hash_value);
    transparent_crc(g_223.f4, "g_223.f4", print_hash_value);
    transparent_crc(g_226.f0, "g_226.f0", print_hash_value);
    transparent_crc(g_226.f1, "g_226.f1", print_hash_value);
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 1; j++)
        {
            for (k = 0; k < 5; k++)
            {
                transparent_crc(g_229[i][j][k].f0, "g_229[i][j][k].f0", print_hash_value);
                transparent_crc(g_229[i][j][k].f1, "g_229[i][j][k].f1", print_hash_value);
                if (print_hash_value) printf("index = [%d][%d][%d]\n", i, j, k);

            }
        }
    }
    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 9; j++)
        {
            for (k = 0; k < 4; k++)
            {
                transparent_crc(g_231[i][j][k].f1, "g_231[i][j][k].f1", print_hash_value);
                if (print_hash_value) printf("index = [%d][%d][%d]\n", i, j, k);

            }
        }
    }
    transparent_crc(g_245, "g_245", print_hash_value);
    transparent_crc(g_255.f0, "g_255.f0", print_hash_value);
    transparent_crc(g_255.f1, "g_255.f1", print_hash_value);
    transparent_crc(g_319, "g_319", print_hash_value);
    transparent_crc(g_375, "g_375", print_hash_value);
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 1; j++)
        {
            for (k = 0; k < 4; k++)
            {
                transparent_crc(g_428[i][j][k].f0, "g_428[i][j][k].f0", print_hash_value);
                transparent_crc(g_428[i][j][k].f1, "g_428[i][j][k].f1", print_hash_value);
                if (print_hash_value) printf("index = [%d][%d][%d]\n", i, j, k);

            }
        }
    }
    transparent_crc(g_444, "g_444", print_hash_value);
    transparent_crc(g_479, "g_479", print_hash_value);
    transparent_crc(g_507, "g_507", print_hash_value);
    transparent_crc(g_627, "g_627", print_hash_value);
    transparent_crc(g_706, "g_706", print_hash_value);
    transparent_crc(g_814.f0, "g_814.f0", print_hash_value);
    transparent_crc(g_814.f1, "g_814.f1", print_hash_value);
    transparent_crc(g_814.f2, "g_814.f2", print_hash_value);
    transparent_crc(g_814.f4, "g_814.f4", print_hash_value);
    transparent_crc(g_1007, "g_1007", print_hash_value);
    transparent_crc(g_1178, "g_1178", print_hash_value);
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 6; j++)
        {
            transparent_crc(g_1198[i][j], "g_1198[i][j]", print_hash_value);
            if (print_hash_value) printf("index = [%d][%d]\n", i, j);

        }
    }
    transparent_crc(g_1232, "g_1232", print_hash_value);
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 1; j++)
        {
            for (k = 0; k < 5; k++)
            {
                transparent_crc(g_1399[i][j][k], "g_1399[i][j][k]", print_hash_value);
                if (print_hash_value) printf("index = [%d][%d][%d]\n", i, j, k);

            }
        }
    }
    for (i = 0; i < 2; i++)
    {
        transparent_crc(g_1574[i].f0, "g_1574[i].f0", print_hash_value);
        transparent_crc(g_1574[i].f1, "g_1574[i].f1", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_1582, "g_1582", print_hash_value);
    transparent_crc(g_1693, "g_1693", print_hash_value);
    transparent_crc(g_1695, "g_1695", print_hash_value);
    transparent_crc(g_1743, "g_1743", print_hash_value);
    transparent_crc(g_1771, "g_1771", print_hash_value);
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 4; j++)
        {
            for (k = 0; k < 3; k++)
            {
                transparent_crc(g_1864[i][j][k], "g_1864[i][j][k]", print_hash_value);
                if (print_hash_value) printf("index = [%d][%d][%d]\n", i, j, k);

            }
        }
    }
    transparent_crc(g_2120, "g_2120", print_hash_value);
    platform_main_end(crc32_context ^ 0xFFFFFFFFUL, print_hash_value);
    return 0;
}