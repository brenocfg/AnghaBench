#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_14__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_28__ {int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_27__ {int /*<<< orphan*/  f0; } ;
struct TYPE_26__ {int /*<<< orphan*/  f3; int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_25__ {int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_24__ {int /*<<< orphan*/  f3; int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_23__ {int /*<<< orphan*/  f0; } ;
struct TYPE_22__ {int /*<<< orphan*/  f6; int /*<<< orphan*/  f5; int /*<<< orphan*/  f4; int /*<<< orphan*/  f3; int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_21__ {int /*<<< orphan*/  f0; } ;
struct TYPE_20__ {int /*<<< orphan*/  f3; int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_19__ {int /*<<< orphan*/  f6; int /*<<< orphan*/  f5; int /*<<< orphan*/  f4; int /*<<< orphan*/  f3; int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_18__ {int /*<<< orphan*/  f0; } ;
struct TYPE_17__ {int /*<<< orphan*/  f0; } ;
struct TYPE_16__ {int /*<<< orphan*/  f0; } ;
struct TYPE_15__ {int /*<<< orphan*/  f0; } ;

/* Variables and functions */
 int crc32_context ; 
 int /*<<< orphan*/  crc32_gentab () ; 
 int /*<<< orphan*/  func_1 () ; 
 int /*<<< orphan*/  g_103 ; 
 int /*<<< orphan*/  g_1054 ; 
 int /*<<< orphan*/  g_1055 ; 
 int /*<<< orphan*/ ** g_1057 ; 
 TYPE_14__ g_108 ; 
 TYPE_13__ g_109 ; 
 TYPE_12__ g_110 ; 
 TYPE_11__ g_183 ; 
 TYPE_10__ g_218 ; 
 TYPE_9__ g_25 ; 
 int /*<<< orphan*/  g_258 ; 
 int /*<<< orphan*/  g_332 ; 
 TYPE_8__** g_345 ; 
 int /*<<< orphan*/ * g_393 ; 
 int /*<<< orphan*/  g_395 ; 
 int /*<<< orphan*/  g_398 ; 
 TYPE_7__*** g_404 ; 
 int /*<<< orphan*/  g_452 ; 
 int /*<<< orphan*/  g_454 ; 
 int /*<<< orphan*/ * g_455 ; 
 int /*<<< orphan*/  g_465 ; 
 int /*<<< orphan*/  g_466 ; 
 int /*<<< orphan*/  g_467 ; 
 TYPE_6__* g_49 ; 
 int /*<<< orphan*/  g_5 ; 
 int /*<<< orphan*/  g_518 ; 
 int /*<<< orphan*/  g_52 ; 
 TYPE_5__ g_525 ; 
 int /*<<< orphan*/  g_531 ; 
 int /*<<< orphan*/  g_532 ; 
 int /*<<< orphan*/  g_534 ; 
 int /*<<< orphan*/ *** g_535 ; 
 int /*<<< orphan*/  g_538 ; 
 int /*<<< orphan*/  g_557 ; 
 int /*<<< orphan*/  g_575 ; 
 TYPE_4__** g_591 ; 
 TYPE_3__ g_623 ; 
 int /*<<< orphan*/ ** g_815 ; 
 int /*<<< orphan*/  g_82 ; 
 int /*<<< orphan*/  g_90 ; 
 TYPE_2__ g_901 ; 
 int /*<<< orphan*/  g_92 ; 
 int /*<<< orphan*/  g_96 ; 
 TYPE_1__ g_99 ; 
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
    transparent_crc(g_5, "g_5", print_hash_value);
    transparent_crc(g_25.f0, "g_25.f0", print_hash_value);
    transparent_crc(g_25.f1, "g_25.f1", print_hash_value);
    for (i = 0; i < 9; i++)
    {
        transparent_crc(g_49[i].f0, "g_49[i].f0", print_hash_value);
        transparent_crc(g_49[i].f1, "g_49[i].f1", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_52, "g_52", print_hash_value);
    transparent_crc(g_82, "g_82", print_hash_value);
    transparent_crc(g_90, "g_90", print_hash_value);
    transparent_crc(g_92, "g_92", print_hash_value);
    transparent_crc(g_96, "g_96", print_hash_value);
    transparent_crc(g_99.f0, "g_99.f0", print_hash_value);
    transparent_crc(g_99.f1, "g_99.f1", print_hash_value);
    transparent_crc(g_99.f2, "g_99.f2", print_hash_value);
    transparent_crc(g_99.f3, "g_99.f3", print_hash_value);
    transparent_crc(g_103, "g_103", print_hash_value);
    transparent_crc(g_108.f0, "g_108.f0", print_hash_value);
    transparent_crc(g_108.f1, "g_108.f1", print_hash_value);
    transparent_crc(g_108.f2, "g_108.f2", print_hash_value);
    transparent_crc(g_108.f3, "g_108.f3", print_hash_value);
    transparent_crc(g_108.f4, "g_108.f4", print_hash_value);
    transparent_crc(g_108.f5, "g_108.f5", print_hash_value);
    transparent_crc(g_108.f6, "g_108.f6", print_hash_value);
    transparent_crc(g_109.f0, "g_109.f0", print_hash_value);
    transparent_crc(g_110.f0, "g_110.f0", print_hash_value);
    transparent_crc(g_183.f0, "g_183.f0", print_hash_value);
    transparent_crc(g_218.f0, "g_218.f0", print_hash_value);
    transparent_crc(g_258, "g_258", print_hash_value);
    transparent_crc(g_332, "g_332", print_hash_value);
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 1; j++)
        {
            transparent_crc(g_345[i][j].f0, "g_345[i][j].f0", print_hash_value);
            if (print_hash_value) printf("index = [%d][%d]\n", i, j);

        }
    }
    for (i = 0; i < 6; i++)
    {
        transparent_crc(g_393[i], "g_393[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_395, "g_395", print_hash_value);
    transparent_crc(g_398, "g_398", print_hash_value);
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 3; j++)
        {
            for (k = 0; k < 7; k++)
            {
                transparent_crc(g_404[i][j][k].f0, "g_404[i][j][k].f0", print_hash_value);
                transparent_crc(g_404[i][j][k].f1, "g_404[i][j][k].f1", print_hash_value);
                transparent_crc(g_404[i][j][k].f2, "g_404[i][j][k].f2", print_hash_value);
                transparent_crc(g_404[i][j][k].f3, "g_404[i][j][k].f3", print_hash_value);
                if (print_hash_value) printf("index = [%d][%d][%d]\n", i, j, k);

            }
        }
    }
    transparent_crc(g_452, "g_452", print_hash_value);
    transparent_crc(g_454, "g_454", print_hash_value);
    for (i = 0; i < 1; i++)
    {
        transparent_crc(g_455[i], "g_455[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_465, "g_465", print_hash_value);
    transparent_crc(g_466, "g_466", print_hash_value);
    transparent_crc(g_467, "g_467", print_hash_value);
    transparent_crc(g_518, "g_518", print_hash_value);
    transparent_crc(g_525.f0, "g_525.f0", print_hash_value);
    transparent_crc(g_525.f1, "g_525.f1", print_hash_value);
    transparent_crc(g_525.f2, "g_525.f2", print_hash_value);
    transparent_crc(g_525.f3, "g_525.f3", print_hash_value);
    transparent_crc(g_531, "g_531", print_hash_value);
    transparent_crc(g_532, "g_532", print_hash_value);
    transparent_crc(g_534, "g_534", print_hash_value);
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 6; j++)
        {
            for (k = 0; k < 4; k++)
            {
                transparent_crc(g_535[i][j][k], "g_535[i][j][k]", print_hash_value);
                if (print_hash_value) printf("index = [%d][%d][%d]\n", i, j, k);

            }
        }
    }
    transparent_crc(g_538, "g_538", print_hash_value);
    transparent_crc(g_557, "g_557", print_hash_value);
    transparent_crc(g_575, "g_575", print_hash_value);
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 8; j++)
        {
            transparent_crc(g_591[i][j].f0, "g_591[i][j].f0", print_hash_value);
            if (print_hash_value) printf("index = [%d][%d]\n", i, j);

        }
    }
    transparent_crc(g_623.f0, "g_623.f0", print_hash_value);
    transparent_crc(g_623.f1, "g_623.f1", print_hash_value);
    transparent_crc(g_623.f2, "g_623.f2", print_hash_value);
    transparent_crc(g_623.f3, "g_623.f3", print_hash_value);
    transparent_crc(g_623.f4, "g_623.f4", print_hash_value);
    transparent_crc(g_623.f5, "g_623.f5", print_hash_value);
    transparent_crc(g_623.f6, "g_623.f6", print_hash_value);
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 3; j++)
        {
            transparent_crc(g_815[i][j], "g_815[i][j]", print_hash_value);
            if (print_hash_value) printf("index = [%d][%d]\n", i, j);

        }
    }
    transparent_crc(g_901.f0, "g_901.f0", print_hash_value);
    transparent_crc(g_1054, "g_1054", print_hash_value);
    transparent_crc(g_1055, "g_1055", print_hash_value);
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 5; j++)
        {
            transparent_crc(g_1057[i][j], "g_1057[i][j]", print_hash_value);
            if (print_hash_value) printf("index = [%d][%d]\n", i, j);

        }
    }
    platform_main_end(crc32_context ^ 0xFFFFFFFFUL, print_hash_value);
    return 0;
}