#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  f9; int /*<<< orphan*/  f8; int /*<<< orphan*/  f7; int /*<<< orphan*/  f6; int /*<<< orphan*/  f5; int /*<<< orphan*/  f4; int /*<<< orphan*/  f3; int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_11__ {int /*<<< orphan*/  f4; int /*<<< orphan*/  f3; int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_10__ {int /*<<< orphan*/  f4; int /*<<< orphan*/  f3; int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_9__ {int /*<<< orphan*/  f9; int /*<<< orphan*/  f8; int /*<<< orphan*/  f7; int /*<<< orphan*/  f6; int /*<<< orphan*/  f5; int /*<<< orphan*/  f4; int /*<<< orphan*/  f3; int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_8__ {int /*<<< orphan*/  f4; int /*<<< orphan*/  f3; int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_7__ {int /*<<< orphan*/  f4; int /*<<< orphan*/  f3; int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;

/* Variables and functions */
 int crc32_context ; 
 int /*<<< orphan*/  crc32_gentab () ; 
 int /*<<< orphan*/  func_1 () ; 
 int /*<<< orphan*/  g_1052 ; 
 int /*<<< orphan*/ * g_1105 ; 
 int /*<<< orphan*/  g_1109 ; 
 TYPE_6__ g_1113 ; 
 TYPE_5__ g_1169 ; 
 int /*<<< orphan*/  g_119 ; 
 int /*<<< orphan*/ ** g_1192 ; 
 int /*<<< orphan*/ * g_1233 ; 
 int /*<<< orphan*/  g_1263 ; 
 int /*<<< orphan*/  g_1389 ; 
 TYPE_4__ g_18 ; 
 int /*<<< orphan*/  g_195 ; 
 int /*<<< orphan*/  g_2 ; 
 int /*<<< orphan*/  g_208 ; 
 int /*<<< orphan*/  g_209 ; 
 int /*<<< orphan*/  g_222 ; 
 int /*<<< orphan*/  g_237 ; 
 int /*<<< orphan*/  g_238 ; 
 int /*<<< orphan*/  g_240 ; 
 int /*<<< orphan*/  g_241 ; 
 int /*<<< orphan*/  g_251 ; 
 int /*<<< orphan*/  g_279 ; 
 int /*<<< orphan*/  g_280 ; 
 int /*<<< orphan*/  g_281 ; 
 int /*<<< orphan*/  g_282 ; 
 int /*<<< orphan*/  g_347 ; 
 int /*<<< orphan*/ * g_36 ; 
 int /*<<< orphan*/  g_39 ; 
 TYPE_3__ g_391 ; 
 int /*<<< orphan*/  g_40 ; 
 int /*<<< orphan*/  g_408 ; 
 int /*<<< orphan*/  g_433 ; 
 int /*<<< orphan*/  g_434 ; 
 int /*<<< orphan*/ ** g_499 ; 
 int /*<<< orphan*/  g_5 ; 
 int /*<<< orphan*/  g_500 ; 
 int /*<<< orphan*/  g_501 ; 
 TYPE_2__*** g_508 ; 
 int /*<<< orphan*/ * g_537 ; 
 int /*<<< orphan*/  g_540 ; 
 int /*<<< orphan*/  g_541 ; 
 int /*<<< orphan*/  g_542 ; 
 int /*<<< orphan*/  g_553 ; 
 int /*<<< orphan*/ ** g_555 ; 
 int /*<<< orphan*/  g_564 ; 
 int /*<<< orphan*/  g_71 ; 
 int /*<<< orphan*/  g_79 ; 
 int /*<<< orphan*/  g_802 ; 
 int /*<<< orphan*/ *** g_809 ; 
 TYPE_1__ g_82 ; 
 int /*<<< orphan*/  g_876 ; 
 int /*<<< orphan*/  g_910 ; 
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
    transparent_crc(g_5, "g_5", print_hash_value);
    transparent_crc(g_18.f0, "g_18.f0", print_hash_value);
    transparent_crc(g_18.f1, "g_18.f1", print_hash_value);
    transparent_crc(g_18.f2, "g_18.f2", print_hash_value);
    transparent_crc(g_18.f3, "g_18.f3", print_hash_value);
    transparent_crc(g_18.f4, "g_18.f4", print_hash_value);
    for (i = 0; i < 8; i++)
    {
        transparent_crc(g_36[i], "g_36[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_39, "g_39", print_hash_value);
    transparent_crc(g_40, "g_40", print_hash_value);
    transparent_crc(g_71, "g_71", print_hash_value);
    transparent_crc(g_79, "g_79", print_hash_value);
    transparent_crc(g_82.f0, "g_82.f0", print_hash_value);
    transparent_crc(g_82.f1, "g_82.f1", print_hash_value);
    transparent_crc(g_82.f2, "g_82.f2", print_hash_value);
    transparent_crc(g_82.f3, "g_82.f3", print_hash_value);
    transparent_crc(g_82.f4, "g_82.f4", print_hash_value);
    transparent_crc(g_119, "g_119", print_hash_value);
    transparent_crc(g_195, "g_195", print_hash_value);
    transparent_crc(g_208, "g_208", print_hash_value);
    transparent_crc(g_209, "g_209", print_hash_value);
    transparent_crc(g_222, "g_222", print_hash_value);
    transparent_crc(g_237, "g_237", print_hash_value);
    transparent_crc(g_238, "g_238", print_hash_value);
    transparent_crc(g_240, "g_240", print_hash_value);
    transparent_crc(g_241, "g_241", print_hash_value);
    transparent_crc(g_251, "g_251", print_hash_value);
    transparent_crc(g_279, "g_279", print_hash_value);
    transparent_crc(g_280, "g_280", print_hash_value);
    transparent_crc(g_281, "g_281", print_hash_value);
    transparent_crc(g_282, "g_282", print_hash_value);
    transparent_crc(g_347, "g_347", print_hash_value);
    transparent_crc(g_391.f0, "g_391.f0", print_hash_value);
    transparent_crc(g_391.f1, "g_391.f1", print_hash_value);
    transparent_crc(g_391.f2, "g_391.f2", print_hash_value);
    transparent_crc(g_391.f3, "g_391.f3", print_hash_value);
    transparent_crc(g_391.f4, "g_391.f4", print_hash_value);
    transparent_crc(g_391.f5, "g_391.f5", print_hash_value);
    transparent_crc(g_391.f6, "g_391.f6", print_hash_value);
    transparent_crc(g_391.f7, "g_391.f7", print_hash_value);
    transparent_crc(g_391.f8, "g_391.f8", print_hash_value);
    transparent_crc(g_391.f9, "g_391.f9", print_hash_value);
    transparent_crc(g_408, "g_408", print_hash_value);
    transparent_crc(g_433, "g_433", print_hash_value);
    transparent_crc(g_434, "g_434", print_hash_value);
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 1; j++)
        {
            transparent_crc(g_499[i][j], "g_499[i][j]", print_hash_value);
            if (print_hash_value) printf("index = [%d][%d]\n", i, j);

        }
    }
    transparent_crc(g_500, "g_500", print_hash_value);
    transparent_crc(g_501, "g_501", print_hash_value);
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 4; j++)
        {
            for (k = 0; k < 7; k++)
            {
                transparent_crc(g_508[i][j][k].f0, "g_508[i][j][k].f0", print_hash_value);
                transparent_crc(g_508[i][j][k].f1, "g_508[i][j][k].f1", print_hash_value);
                transparent_crc(g_508[i][j][k].f2, "g_508[i][j][k].f2", print_hash_value);
                transparent_crc(g_508[i][j][k].f3, "g_508[i][j][k].f3", print_hash_value);
                transparent_crc(g_508[i][j][k].f4, "g_508[i][j][k].f4", print_hash_value);
                if (print_hash_value) printf("index = [%d][%d][%d]\n", i, j, k);

            }
        }
    }
    for (i = 0; i < 3; i++)
    {
        transparent_crc(g_537[i], "g_537[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_540, "g_540", print_hash_value);
    transparent_crc(g_541, "g_541", print_hash_value);
    transparent_crc(g_542, "g_542", print_hash_value);
    transparent_crc(g_553, "g_553", print_hash_value);
    for (i = 0; i < 1; i++)
    {
        for (j = 0; j < 2; j++)
        {
            transparent_crc(g_555[i][j], "g_555[i][j]", print_hash_value);
            if (print_hash_value) printf("index = [%d][%d]\n", i, j);

        }
    }
    transparent_crc(g_564, "g_564", print_hash_value);
    transparent_crc(g_802, "g_802", print_hash_value);
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 1; j++)
        {
            for (k = 0; k < 8; k++)
            {
                transparent_crc(g_809[i][j][k], "g_809[i][j][k]", print_hash_value);
                if (print_hash_value) printf("index = [%d][%d][%d]\n", i, j, k);

            }
        }
    }
    transparent_crc(g_876, "g_876", print_hash_value);
    transparent_crc(g_910, "g_910", print_hash_value);
    transparent_crc(g_1052, "g_1052", print_hash_value);
    for (i = 0; i < 9; i++)
    {
        transparent_crc(g_1105[i], "g_1105[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_1109, "g_1109", print_hash_value);
    transparent_crc(g_1113.f0, "g_1113.f0", print_hash_value);
    transparent_crc(g_1113.f1, "g_1113.f1", print_hash_value);
    transparent_crc(g_1113.f2, "g_1113.f2", print_hash_value);
    transparent_crc(g_1113.f3, "g_1113.f3", print_hash_value);
    transparent_crc(g_1113.f4, "g_1113.f4", print_hash_value);
    transparent_crc(g_1113.f5, "g_1113.f5", print_hash_value);
    transparent_crc(g_1113.f6, "g_1113.f6", print_hash_value);
    transparent_crc(g_1113.f7, "g_1113.f7", print_hash_value);
    transparent_crc(g_1113.f8, "g_1113.f8", print_hash_value);
    transparent_crc(g_1113.f9, "g_1113.f9", print_hash_value);
    transparent_crc(g_1169.f0, "g_1169.f0", print_hash_value);
    transparent_crc(g_1169.f1, "g_1169.f1", print_hash_value);
    transparent_crc(g_1169.f2, "g_1169.f2", print_hash_value);
    transparent_crc(g_1169.f3, "g_1169.f3", print_hash_value);
    transparent_crc(g_1169.f4, "g_1169.f4", print_hash_value);
    for (i = 0; i < 1; i++)
    {
        for (j = 0; j < 8; j++)
        {
            transparent_crc(g_1192[i][j], "g_1192[i][j]", print_hash_value);
            if (print_hash_value) printf("index = [%d][%d]\n", i, j);

        }
    }
    for (i = 0; i < 8; i++)
    {
        transparent_crc(g_1233[i], "g_1233[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_1263, "g_1263", print_hash_value);
    transparent_crc(g_1389, "g_1389", print_hash_value);
    platform_main_end(crc32_context ^ 0xFFFFFFFFUL, print_hash_value);
    return 0;
}