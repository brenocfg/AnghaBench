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
struct TYPE_10__ {int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_9__ {int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_8__ {int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_7__ {int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_6__ {int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;

/* Variables and functions */
 int crc32_context ; 
 int /*<<< orphan*/  crc32_gentab () ; 
 int /*<<< orphan*/  func_1 () ; 
 int /*<<< orphan*/  g_101 ; 
 int /*<<< orphan*/ * g_1048 ; 
 int /*<<< orphan*/  g_105 ; 
 int /*<<< orphan*/  g_1077 ; 
 int /*<<< orphan*/  g_1127 ; 
 int /*<<< orphan*/  g_1144 ; 
 int /*<<< orphan*/  g_1213 ; 
 int /*<<< orphan*/  g_1310 ; 
 int /*<<< orphan*/  g_1334 ; 
 int /*<<< orphan*/  g_1388 ; 
 TYPE_5__ g_1428 ; 
 int /*<<< orphan*/ * g_1464 ; 
 int /*<<< orphan*/  g_1489 ; 
 TYPE_4__ g_1512 ; 
 int /*<<< orphan*/  g_1527 ; 
 int /*<<< orphan*/ * g_154 ; 
 int /*<<< orphan*/  g_1685 ; 
 int /*<<< orphan*/  g_1935 ; 
 int /*<<< orphan*/ * g_2047 ; 
 int /*<<< orphan*/ * g_209 ; 
 int /*<<< orphan*/ ** g_212 ; 
 int /*<<< orphan*/ ** g_220 ; 
 int /*<<< orphan*/  g_221 ; 
 int /*<<< orphan*/  g_222 ; 
 TYPE_3__* g_27 ; 
 int /*<<< orphan*/  g_272 ; 
 int /*<<< orphan*/  g_275 ; 
 int /*<<< orphan*/  g_283 ; 
 int /*<<< orphan*/  g_292 ; 
 TYPE_2__ g_31 ; 
 int /*<<< orphan*/  g_313 ; 
 int /*<<< orphan*/ * g_361 ; 
 int /*<<< orphan*/  g_363 ; 
 int /*<<< orphan*/  g_364 ; 
 int /*<<< orphan*/  g_382 ; 
 int /*<<< orphan*/  g_383 ; 
 int /*<<< orphan*/  g_386 ; 
 int /*<<< orphan*/  g_4 ; 
 int /*<<< orphan*/  g_400 ; 
 int /*<<< orphan*/ * g_422 ; 
 int /*<<< orphan*/  g_425 ; 
 int /*<<< orphan*/ *** g_431 ; 
 int /*<<< orphan*/ * g_436 ; 
 int /*<<< orphan*/  g_439 ; 
 int /*<<< orphan*/  g_443 ; 
 int /*<<< orphan*/  g_460 ; 
 int /*<<< orphan*/  g_465 ; 
 TYPE_1__ g_679 ; 
 int /*<<< orphan*/ * g_705 ; 
 int /*<<< orphan*/ * g_715 ; 
 int /*<<< orphan*/  g_716 ; 
 int /*<<< orphan*/  g_767 ; 
 int /*<<< orphan*/  g_93 ; 
 int /*<<< orphan*/ ** g_941 ; 
 int /*<<< orphan*/ *** g_951 ; 
 int /*<<< orphan*/  g_986 ; 
 int /*<<< orphan*/  g_99 ; 
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
    for (i = 0; i < 1; i++)
    {
        transparent_crc(g_27[i].f0, "g_27[i].f0", print_hash_value);
        transparent_crc(g_27[i].f1, "g_27[i].f1", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_31.f0, "g_31.f0", print_hash_value);
    transparent_crc(g_31.f1, "g_31.f1", print_hash_value);
    transparent_crc(g_93, "g_93", print_hash_value);
    transparent_crc(g_99, "g_99", print_hash_value);
    transparent_crc(g_101, "g_101", print_hash_value);
    transparent_crc(g_105, "g_105", print_hash_value);
    for (i = 0; i < 9; i++)
    {
        transparent_crc(g_154[i], "g_154[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    for (i = 0; i < 7; i++)
    {
        transparent_crc(g_209[i], "g_209[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    for (i = 0; i < 7; i++)
    {
        for (j = 0; j < 1; j++)
        {
            transparent_crc(g_212[i][j], "g_212[i][j]", print_hash_value);
            if (print_hash_value) printf("index = [%d][%d]\n", i, j);

        }
    }
    for (i = 0; i < 1; i++)
    {
        for (j = 0; j < 6; j++)
        {
            transparent_crc(g_220[i][j], "g_220[i][j]", print_hash_value);
            if (print_hash_value) printf("index = [%d][%d]\n", i, j);

        }
    }
    transparent_crc(g_221, "g_221", print_hash_value);
    transparent_crc(g_222, "g_222", print_hash_value);
    transparent_crc(g_272, "g_272", print_hash_value);
    transparent_crc(g_275, "g_275", print_hash_value);
    transparent_crc(g_283, "g_283", print_hash_value);
    transparent_crc(g_292, "g_292", print_hash_value);
    transparent_crc(g_313, "g_313", print_hash_value);
    for (i = 0; i < 3; i++)
    {
        transparent_crc(g_361[i], "g_361[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_363, "g_363", print_hash_value);
    transparent_crc(g_364, "g_364", print_hash_value);
    transparent_crc(g_382, "g_382", print_hash_value);
    transparent_crc(g_383, "g_383", print_hash_value);
    transparent_crc(g_386, "g_386", print_hash_value);
    transparent_crc(g_400, "g_400", print_hash_value);
    for (i = 0; i < 6; i++)
    {
        transparent_crc(g_422[i], "g_422[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_425, "g_425", print_hash_value);
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 9; j++)
        {
            for (k = 0; k < 1; k++)
            {
                transparent_crc(g_431[i][j][k], "g_431[i][j][k]", print_hash_value);
                if (print_hash_value) printf("index = [%d][%d][%d]\n", i, j, k);

            }
        }
    }
    for (i = 0; i < 5; i++)
    {
        transparent_crc(g_436[i], "g_436[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_439, "g_439", print_hash_value);
    transparent_crc(g_443, "g_443", print_hash_value);
    transparent_crc(g_460, "g_460", print_hash_value);
    transparent_crc(g_465, "g_465", print_hash_value);
    transparent_crc(g_679.f0, "g_679.f0", print_hash_value);
    transparent_crc(g_679.f1, "g_679.f1", print_hash_value);
    for (i = 0; i < 10; i++)
    {
        transparent_crc(g_705[i], "g_705[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    for (i = 0; i < 6; i++)
    {
        transparent_crc(g_715[i], "g_715[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_716, "g_716", print_hash_value);
    transparent_crc(g_767, "g_767", print_hash_value);
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 1; j++)
        {
            transparent_crc(g_941[i][j], "g_941[i][j]", print_hash_value);
            if (print_hash_value) printf("index = [%d][%d]\n", i, j);

        }
    }
    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 5; j++)
        {
            for (k = 0; k < 1; k++)
            {
                transparent_crc(g_951[i][j][k], "g_951[i][j][k]", print_hash_value);
                if (print_hash_value) printf("index = [%d][%d][%d]\n", i, j, k);

            }
        }
    }
    transparent_crc(g_986, "g_986", print_hash_value);
    for (i = 0; i < 6; i++)
    {
        transparent_crc(g_1048[i], "g_1048[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_1077, "g_1077", print_hash_value);
    transparent_crc(g_1127, "g_1127", print_hash_value);
    transparent_crc(g_1144, "g_1144", print_hash_value);
    transparent_crc(g_1213, "g_1213", print_hash_value);
    transparent_crc(g_1310, "g_1310", print_hash_value);
    transparent_crc(g_1334, "g_1334", print_hash_value);
    transparent_crc(g_1388, "g_1388", print_hash_value);
    transparent_crc(g_1428.f0, "g_1428.f0", print_hash_value);
    transparent_crc(g_1428.f1, "g_1428.f1", print_hash_value);
    for (i = 0; i < 1; i++)
    {
        transparent_crc(g_1464[i], "g_1464[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_1489, "g_1489", print_hash_value);
    transparent_crc(g_1512.f0, "g_1512.f0", print_hash_value);
    transparent_crc(g_1512.f1, "g_1512.f1", print_hash_value);
    transparent_crc(g_1527, "g_1527", print_hash_value);
    transparent_crc(g_1685, "g_1685", print_hash_value);
    transparent_crc(g_1935, "g_1935", print_hash_value);
    for (i = 0; i < 9; i++)
    {
        transparent_crc(g_2047[i], "g_2047[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    platform_main_end(crc32_context ^ 0xFFFFFFFFUL, print_hash_value);
    return 0;
}