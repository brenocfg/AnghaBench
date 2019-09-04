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
struct TYPE_12__ {int /*<<< orphan*/  f8; int /*<<< orphan*/  f7; int /*<<< orphan*/  f6; int /*<<< orphan*/  f5; int /*<<< orphan*/  f4; int /*<<< orphan*/  f3; int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_11__ {int /*<<< orphan*/  f0; } ;
struct TYPE_10__ {int /*<<< orphan*/  f0; } ;
struct TYPE_9__ {int /*<<< orphan*/  f8; int /*<<< orphan*/  f7; int /*<<< orphan*/  f6; int /*<<< orphan*/  f5; int /*<<< orphan*/  f4; int /*<<< orphan*/  f3; int /*<<< orphan*/  f2; int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_8__ {int /*<<< orphan*/  f0; } ;
struct TYPE_7__ {int /*<<< orphan*/  f0; } ;

/* Variables and functions */
 int crc32_context ; 
 int /*<<< orphan*/  crc32_gentab () ; 
 int /*<<< orphan*/  func_1 () ; 
 int /*<<< orphan*/  g_1058 ; 
 TYPE_6__ g_109 ; 
 int /*<<< orphan*/  g_113 ; 
 int /*<<< orphan*/  g_114 ; 
 TYPE_5__ g_1177 ; 
 int /*<<< orphan*/ ** g_126 ; 
 int /*<<< orphan*/ * g_141 ; 
 int /*<<< orphan*/  g_143 ; 
 int /*<<< orphan*/  g_144 ; 
 int /*<<< orphan*/  g_2 ; 
 int /*<<< orphan*/  g_215 ; 
 int /*<<< orphan*/  g_217 ; 
 int /*<<< orphan*/ *** g_234 ; 
 int /*<<< orphan*/  g_24 ; 
 int /*<<< orphan*/ * g_312 ; 
 TYPE_4__ g_331 ; 
 TYPE_3__** g_350 ; 
 int /*<<< orphan*/  g_36 ; 
 int /*<<< orphan*/  g_408 ; 
 TYPE_2__ g_477 ; 
 int /*<<< orphan*/  g_493 ; 
 int /*<<< orphan*/  g_52 ; 
 int /*<<< orphan*/  g_53 ; 
 int /*<<< orphan*/  g_543 ; 
 int /*<<< orphan*/  g_55 ; 
 int /*<<< orphan*/  g_626 ; 
 int /*<<< orphan*/  g_664 ; 
 int /*<<< orphan*/ *** g_666 ; 
 int /*<<< orphan*/  g_72 ; 
 int /*<<< orphan*/  g_733 ; 
 int /*<<< orphan*/  g_776 ; 
 int /*<<< orphan*/  g_807 ; 
 int /*<<< orphan*/  g_812 ; 
 TYPE_1__ g_824 ; 
 int /*<<< orphan*/  g_825 ; 
 int /*<<< orphan*/  g_891 ; 
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
    transparent_crc(g_24, "g_24", print_hash_value);
    transparent_crc(g_36, "g_36", print_hash_value);
    transparent_crc(g_52, "g_52", print_hash_value);
    transparent_crc(g_53, "g_53", print_hash_value);
    transparent_crc(g_55, "g_55", print_hash_value);
    transparent_crc(g_72, "g_72", print_hash_value);
    transparent_crc(g_109.f0, "g_109.f0", print_hash_value);
    transparent_crc(g_109.f1, "g_109.f1", print_hash_value);
    transparent_crc(g_109.f2, "g_109.f2", print_hash_value);
    transparent_crc(g_109.f3, "g_109.f3", print_hash_value);
    transparent_crc(g_109.f4, "g_109.f4", print_hash_value);
    transparent_crc(g_109.f5, "g_109.f5", print_hash_value);
    transparent_crc(g_109.f6, "g_109.f6", print_hash_value);
    transparent_crc(g_109.f7, "g_109.f7", print_hash_value);
    transparent_crc(g_109.f8, "g_109.f8", print_hash_value);
    transparent_crc(g_113, "g_113", print_hash_value);
    transparent_crc(g_114, "g_114", print_hash_value);
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 6; j++)
        {
            transparent_crc(g_126[i][j], "g_126[i][j]", print_hash_value);
            if (print_hash_value) printf("index = [%d][%d]\n", i, j);

        }
    }
    for (i = 0; i < 2; i++)
    {
        transparent_crc(g_141[i], "g_141[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_143, "g_143", print_hash_value);
    transparent_crc(g_144, "g_144", print_hash_value);
    transparent_crc(g_215, "g_215", print_hash_value);
    transparent_crc(g_217, "g_217", print_hash_value);
    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 6; j++)
        {
            for (k = 0; k < 7; k++)
            {
                transparent_crc(g_234[i][j][k], "g_234[i][j][k]", print_hash_value);
                if (print_hash_value) printf("index = [%d][%d][%d]\n", i, j, k);

            }
        }
    }
    for (i = 0; i < 2; i++)
    {
        transparent_crc(g_312[i], "g_312[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_331.f0, "g_331.f0", print_hash_value);
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 8; j++)
        {
            transparent_crc(g_350[i][j].f0, "g_350[i][j].f0", print_hash_value);
            transparent_crc(g_350[i][j].f1, "g_350[i][j].f1", print_hash_value);
            transparent_crc(g_350[i][j].f2, "g_350[i][j].f2", print_hash_value);
            transparent_crc(g_350[i][j].f3, "g_350[i][j].f3", print_hash_value);
            transparent_crc(g_350[i][j].f4, "g_350[i][j].f4", print_hash_value);
            transparent_crc(g_350[i][j].f5, "g_350[i][j].f5", print_hash_value);
            transparent_crc(g_350[i][j].f6, "g_350[i][j].f6", print_hash_value);
            transparent_crc(g_350[i][j].f7, "g_350[i][j].f7", print_hash_value);
            transparent_crc(g_350[i][j].f8, "g_350[i][j].f8", print_hash_value);
            if (print_hash_value) printf("index = [%d][%d]\n", i, j);

        }
    }
    transparent_crc(g_408, "g_408", print_hash_value);
    transparent_crc(g_477.f0, "g_477.f0", print_hash_value);
    transparent_crc(g_493, "g_493", print_hash_value);
    transparent_crc(g_543, "g_543", print_hash_value);
    transparent_crc(g_626, "g_626", print_hash_value);
    transparent_crc(g_664, "g_664", print_hash_value);
    for (i = 0; i < 1; i++)
    {
        for (j = 0; j < 9; j++)
        {
            for (k = 0; k < 4; k++)
            {
                transparent_crc(g_666[i][j][k], "g_666[i][j][k]", print_hash_value);
                if (print_hash_value) printf("index = [%d][%d][%d]\n", i, j, k);

            }
        }
    }
    transparent_crc(g_733, "g_733", print_hash_value);
    transparent_crc(g_776, "g_776", print_hash_value);
    transparent_crc(g_807, "g_807", print_hash_value);
    transparent_crc(g_812, "g_812", print_hash_value);
    transparent_crc(g_824.f0, "g_824.f0", print_hash_value);
    transparent_crc(g_825, "g_825", print_hash_value);
    transparent_crc(g_891, "g_891", print_hash_value);
    transparent_crc(g_1058, "g_1058", print_hash_value);
    transparent_crc(g_1177.f0, "g_1177.f0", print_hash_value);
    platform_main_end(crc32_context ^ 0xFFFFFFFFUL, print_hash_value);
    return 0;
}