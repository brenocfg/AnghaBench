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
struct TYPE_18__ {int /*<<< orphan*/  f2; int /*<<< orphan*/  f0; } ;
struct TYPE_17__ {int /*<<< orphan*/  f4; int /*<<< orphan*/  f3; int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_11__ {int /*<<< orphan*/  f4; int /*<<< orphan*/  f3; int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_16__ {int /*<<< orphan*/  f4; TYPE_2__ f3; int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_15__ {int /*<<< orphan*/  f2; } ;
struct TYPE_14__ {int /*<<< orphan*/  f4; int /*<<< orphan*/  f3; int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_10__ {int /*<<< orphan*/  f4; int /*<<< orphan*/  f3; int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_13__ {int /*<<< orphan*/  f4; TYPE_1__ f3; int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_12__ {int /*<<< orphan*/  f4; int /*<<< orphan*/  f3; int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;

/* Variables and functions */
 int crc32_context ; 
 int /*<<< orphan*/  crc32_gentab () ; 
 int /*<<< orphan*/  func_1 () ; 
 int /*<<< orphan*/  g_1001 ; 
 TYPE_9__ g_1007 ; 
 int /*<<< orphan*/ ** g_130 ; 
 int /*<<< orphan*/  g_132 ; 
 int /*<<< orphan*/  g_1359 ; 
 int /*<<< orphan*/  g_1361 ; 
 int /*<<< orphan*/  g_140 ; 
 int /*<<< orphan*/ ** g_141 ; 
 int /*<<< orphan*/ * g_1473 ; 
 int /*<<< orphan*/  g_1474 ; 
 int /*<<< orphan*/  g_1492 ; 
 int /*<<< orphan*/  g_1725 ; 
 int /*<<< orphan*/  g_1798 ; 
 TYPE_8__ g_193 ; 
 TYPE_7__ g_203 ; 
 int /*<<< orphan*/  g_2122 ; 
 TYPE_6__ g_23 ; 
 int /*<<< orphan*/  g_2341 ; 
 int /*<<< orphan*/  g_2575 ; 
 TYPE_5__ g_2686 ; 
 int /*<<< orphan*/  g_27 ; 
 int /*<<< orphan*/ ** g_275 ; 
 int /*<<< orphan*/  g_2898 ; 
 int /*<<< orphan*/  g_29 ; 
 int /*<<< orphan*/  g_33 ; 
 int /*<<< orphan*/  g_367 ; 
 int /*<<< orphan*/ *** g_368 ; 
 TYPE_4__*** g_429 ; 
 int /*<<< orphan*/  g_448 ; 
 int /*<<< orphan*/  g_491 ; 
 TYPE_3__ g_663 ; 
 int /*<<< orphan*/ ** g_709 ; 
 int /*<<< orphan*/  g_82 ; 
 int /*<<< orphan*/  g_870 ; 
 int /*<<< orphan*/  g_9 ; 
 int /*<<< orphan*/  g_902 ; 
 int /*<<< orphan*/  g_92 ; 
 int /*<<< orphan*/  g_94 ; 
 int /*<<< orphan*/  g_96 ; 
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
    transparent_crc(g_9, "g_9", print_hash_value);
    transparent_crc(g_23.f2, "g_23.f2", print_hash_value);
    transparent_crc(g_27, "g_27", print_hash_value);
    transparent_crc(g_29, "g_29", print_hash_value);
    transparent_crc(g_33, "g_33", print_hash_value);
    transparent_crc(g_82, "g_82", print_hash_value);
    transparent_crc(g_92, "g_92", print_hash_value);
    transparent_crc(g_94, "g_94", print_hash_value);
    transparent_crc(g_96, "g_96", print_hash_value);
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 6; j++)
        {
            transparent_crc(g_130[i][j], "g_130[i][j]", print_hash_value);
            if (print_hash_value) printf("index = [%d][%d]\n", i, j);

        }
    }
    transparent_crc(g_132, "g_132", print_hash_value);
    transparent_crc(g_140, "g_140", print_hash_value);
    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 7; j++)
        {
            transparent_crc(g_141[i][j], "g_141[i][j]", print_hash_value);
            if (print_hash_value) printf("index = [%d][%d]\n", i, j);

        }
    }
    transparent_crc(g_193.f0, "g_193.f0", print_hash_value);
    transparent_crc(g_193.f1, "g_193.f1", print_hash_value);
    transparent_crc(g_193.f2, "g_193.f2", print_hash_value);
    transparent_crc(g_193.f3, "g_193.f3", print_hash_value);
    transparent_crc(g_193.f4, "g_193.f4", print_hash_value);
    transparent_crc(g_203.f0, "g_203.f0", print_hash_value);
    transparent_crc(g_203.f1, "g_203.f1", print_hash_value);
    transparent_crc(g_203.f2, "g_203.f2", print_hash_value);
    transparent_crc(g_203.f3.f0, "g_203.f3.f0", print_hash_value);
    transparent_crc(g_203.f3.f1, "g_203.f3.f1", print_hash_value);
    transparent_crc(g_203.f3.f2, "g_203.f3.f2", print_hash_value);
    transparent_crc(g_203.f3.f3, "g_203.f3.f3", print_hash_value);
    transparent_crc(g_203.f3.f4, "g_203.f3.f4", print_hash_value);
    transparent_crc(g_203.f4, "g_203.f4", print_hash_value);
    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 3; j++)
        {
            transparent_crc(g_275[i][j], "g_275[i][j]", print_hash_value);
            if (print_hash_value) printf("index = [%d][%d]\n", i, j);

        }
    }
    transparent_crc(g_367, "g_367", print_hash_value);
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 8; j++)
        {
            for (k = 0; k < 3; k++)
            {
                transparent_crc(g_368[i][j][k], "g_368[i][j][k]", print_hash_value);
                if (print_hash_value) printf("index = [%d][%d][%d]\n", i, j, k);

            }
        }
    }
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 6; j++)
        {
            for (k = 0; k < 6; k++)
            {
                transparent_crc(g_429[i][j][k].f0, "g_429[i][j][k].f0", print_hash_value);
                transparent_crc(g_429[i][j][k].f1, "g_429[i][j][k].f1", print_hash_value);
                transparent_crc(g_429[i][j][k].f2, "g_429[i][j][k].f2", print_hash_value);
                transparent_crc(g_429[i][j][k].f3.f0, "g_429[i][j][k].f3.f0", print_hash_value);
                transparent_crc(g_429[i][j][k].f3.f1, "g_429[i][j][k].f3.f1", print_hash_value);
                transparent_crc(g_429[i][j][k].f3.f2, "g_429[i][j][k].f3.f2", print_hash_value);
                transparent_crc(g_429[i][j][k].f3.f3, "g_429[i][j][k].f3.f3", print_hash_value);
                transparent_crc(g_429[i][j][k].f3.f4, "g_429[i][j][k].f3.f4", print_hash_value);
                transparent_crc(g_429[i][j][k].f4, "g_429[i][j][k].f4", print_hash_value);
                if (print_hash_value) printf("index = [%d][%d][%d]\n", i, j, k);

            }
        }
    }
    transparent_crc(g_448, "g_448", print_hash_value);
    transparent_crc(g_491, "g_491", print_hash_value);
    transparent_crc(g_663.f0, "g_663.f0", print_hash_value);
    transparent_crc(g_663.f1, "g_663.f1", print_hash_value);
    transparent_crc(g_663.f2, "g_663.f2", print_hash_value);
    transparent_crc(g_663.f3, "g_663.f3", print_hash_value);
    transparent_crc(g_663.f4, "g_663.f4", print_hash_value);
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 3; j++)
        {
            transparent_crc(g_709[i][j], "g_709[i][j]", print_hash_value);
            if (print_hash_value) printf("index = [%d][%d]\n", i, j);

        }
    }
    transparent_crc(g_870, "g_870", print_hash_value);
    transparent_crc(g_902, "g_902", print_hash_value);
    transparent_crc(g_1001, "g_1001", print_hash_value);
    transparent_crc(g_1007.f0, "g_1007.f0", print_hash_value);
    transparent_crc(g_1007.f2, "g_1007.f2", print_hash_value);
    transparent_crc(g_1359, "g_1359", print_hash_value);
    transparent_crc(g_1361, "g_1361", print_hash_value);
    for (i = 0; i < 9; i++)
    {
        transparent_crc(g_1473[i], "g_1473[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_1474, "g_1474", print_hash_value);
    transparent_crc(g_1492, "g_1492", print_hash_value);
    transparent_crc(g_1725, "g_1725", print_hash_value);
    transparent_crc(g_1798, "g_1798", print_hash_value);
    transparent_crc(g_2122, "g_2122", print_hash_value);
    transparent_crc(g_2341, "g_2341", print_hash_value);
    transparent_crc(g_2575, "g_2575", print_hash_value);
    transparent_crc(g_2686.f0, "g_2686.f0", print_hash_value);
    transparent_crc(g_2686.f1, "g_2686.f1", print_hash_value);
    transparent_crc(g_2686.f2, "g_2686.f2", print_hash_value);
    transparent_crc(g_2686.f3, "g_2686.f3", print_hash_value);
    transparent_crc(g_2686.f4, "g_2686.f4", print_hash_value);
    transparent_crc(g_2898, "g_2898", print_hash_value);
    platform_main_end(crc32_context ^ 0xFFFFFFFFUL, print_hash_value);
    return 0;
}