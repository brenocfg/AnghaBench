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
struct TYPE_9__ {int /*<<< orphan*/  f4; int /*<<< orphan*/  f2; } ;
struct TYPE_8__ {int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_7__ {int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_6__ {int /*<<< orphan*/  f0; } ;

/* Variables and functions */
 int crc32_context ; 
 int /*<<< orphan*/  crc32_gentab () ; 
 int /*<<< orphan*/  func_1 () ; 
 int /*<<< orphan*/  g_102 ; 
 TYPE_5__** g_1059 ; 
 int /*<<< orphan*/  g_11 ; 
 int /*<<< orphan*/  g_1124 ; 
 int /*<<< orphan*/  g_1254 ; 
 int /*<<< orphan*/  g_1294 ; 
 int /*<<< orphan*/  g_135 ; 
 int /*<<< orphan*/  g_1418 ; 
 int /*<<< orphan*/  g_144 ; 
 int /*<<< orphan*/  g_1501 ; 
 int /*<<< orphan*/  g_1597 ; 
 int /*<<< orphan*/  g_160 ; 
 int /*<<< orphan*/  g_1613 ; 
 int /*<<< orphan*/ * g_1665 ; 
 TYPE_4__ g_181 ; 
 TYPE_3__ g_202 ; 
 int /*<<< orphan*/  g_209 ; 
 int /*<<< orphan*/  g_211 ; 
 int /*<<< orphan*/  g_231 ; 
 int /*<<< orphan*/  g_328 ; 
 int /*<<< orphan*/  g_390 ; 
 int /*<<< orphan*/  g_468 ; 
 int /*<<< orphan*/  g_547 ; 
 int /*<<< orphan*/  g_573 ; 
 int /*<<< orphan*/  g_575 ; 
 int /*<<< orphan*/  g_582 ; 
 TYPE_2__ g_649 ; 
 int /*<<< orphan*/ * g_66 ; 
 int /*<<< orphan*/  g_666 ; 
 int /*<<< orphan*/  g_668 ; 
 int /*<<< orphan*/  g_71 ; 
 int /*<<< orphan*/  g_75 ; 
 int /*<<< orphan*/  g_756 ; 
 int /*<<< orphan*/ * g_76 ; 
 int /*<<< orphan*/  g_77 ; 
 int /*<<< orphan*/ ** g_78 ; 
 int /*<<< orphan*/  g_860 ; 
 int /*<<< orphan*/  g_894 ; 
 TYPE_1__* g_9 ; 
 int /*<<< orphan*/  g_947 ; 
 int /*<<< orphan*/ ** g_966 ; 
 int /*<<< orphan*/  platform_main_begin () ; 
 int /*<<< orphan*/  platform_main_end (int,int) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  transparent_crc (int /*<<< orphan*/ ,char*,int) ; 

int main (int argc, char* argv[])
{
    int i, j;
    int print_hash_value = 0;
    if (argc == 2 && strcmp(argv[1], "1") == 0) print_hash_value = 1;
    platform_main_begin();
    crc32_gentab();
    func_1();
    for (i = 0; i < 5; i++)
    {
        transparent_crc(g_9[i].f0, "g_9[i].f0", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_11, "g_11", print_hash_value);
    for (i = 0; i < 1; i++)
    {
        transparent_crc(g_66[i], "g_66[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_71, "g_71", print_hash_value);
    transparent_crc(g_75, "g_75", print_hash_value);
    for (i = 0; i < 5; i++)
    {
        transparent_crc(g_76[i], "g_76[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_77, "g_77", print_hash_value);
    for (i = 0; i < 7; i++)
    {
        for (j = 0; j < 9; j++)
        {
            transparent_crc(g_78[i][j], "g_78[i][j]", print_hash_value);
            if (print_hash_value) printf("index = [%d][%d]\n", i, j);

        }
    }
    transparent_crc(g_102, "g_102", print_hash_value);
    transparent_crc(g_135, "g_135", print_hash_value);
    transparent_crc(g_144, "g_144", print_hash_value);
    transparent_crc(g_160, "g_160", print_hash_value);
    transparent_crc(g_181.f2, "g_181.f2", print_hash_value);
    transparent_crc(g_181.f4, "g_181.f4", print_hash_value);
    transparent_crc(g_202.f0, "g_202.f0", print_hash_value);
    transparent_crc(g_202.f1, "g_202.f1", print_hash_value);
    transparent_crc(g_209, "g_209", print_hash_value);
    transparent_crc(g_211, "g_211", print_hash_value);
    transparent_crc(g_231, "g_231", print_hash_value);
    transparent_crc(g_328, "g_328", print_hash_value);
    transparent_crc(g_390, "g_390", print_hash_value);
    transparent_crc(g_468, "g_468", print_hash_value);
    transparent_crc(g_547, "g_547", print_hash_value);
    transparent_crc(g_573, "g_573", print_hash_value);
    transparent_crc(g_575, "g_575", print_hash_value);
    transparent_crc(g_582, "g_582", print_hash_value);
    transparent_crc(g_649.f0, "g_649.f0", print_hash_value);
    transparent_crc(g_649.f1, "g_649.f1", print_hash_value);
    transparent_crc(g_666, "g_666", print_hash_value);
    transparent_crc(g_668, "g_668", print_hash_value);
    transparent_crc(g_756, "g_756", print_hash_value);
    transparent_crc(g_860, "g_860", print_hash_value);
    transparent_crc(g_894, "g_894", print_hash_value);
    transparent_crc(g_947, "g_947", print_hash_value);
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 3; j++)
        {
            transparent_crc(g_966[i][j], "g_966[i][j]", print_hash_value);
            if (print_hash_value) printf("index = [%d][%d]\n", i, j);

        }
    }
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            transparent_crc(g_1059[i][j].f0, "g_1059[i][j].f0", print_hash_value);
            transparent_crc(g_1059[i][j].f1, "g_1059[i][j].f1", print_hash_value);
            if (print_hash_value) printf("index = [%d][%d]\n", i, j);

        }
    }
    transparent_crc(g_1124, "g_1124", print_hash_value);
    transparent_crc(g_1254, "g_1254", print_hash_value);
    transparent_crc(g_1294, "g_1294", print_hash_value);
    transparent_crc(g_1418, "g_1418", print_hash_value);
    transparent_crc(g_1501, "g_1501", print_hash_value);
    transparent_crc(g_1597, "g_1597", print_hash_value);
    transparent_crc(g_1613, "g_1613", print_hash_value);
    for (i = 0; i < 1; i++)
    {
        transparent_crc(g_1665[i], "g_1665[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    platform_main_end(crc32_context ^ 0xFFFFFFFFUL, print_hash_value);
    return 0;
}