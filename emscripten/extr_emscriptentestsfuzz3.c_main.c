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
struct TYPE_6__ {int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_5__ {int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;
struct TYPE_4__ {int /*<<< orphan*/  f2; } ;

/* Variables and functions */
 int crc32_context ; 
 int /*<<< orphan*/  crc32_gentab () ; 
 int /*<<< orphan*/  func_1 () ; 
 int /*<<< orphan*/  g_117 ; 
 TYPE_3__ g_163 ; 
 int /*<<< orphan*/ * g_165 ; 
 int /*<<< orphan*/ *** g_171 ; 
 int /*<<< orphan*/  g_218 ; 
 int /*<<< orphan*/  g_23 ; 
 int /*<<< orphan*/  g_234 ; 
 int /*<<< orphan*/  g_246 ; 
 int /*<<< orphan*/  g_25 ; 
 int /*<<< orphan*/  g_255 ; 
 int /*<<< orphan*/  g_34 ; 
 int /*<<< orphan*/  g_380 ; 
 int /*<<< orphan*/  g_387 ; 
 TYPE_2__** g_405 ; 
 TYPE_1__ g_42 ; 
 int /*<<< orphan*/  g_471 ; 
 int /*<<< orphan*/  g_555 ; 
 int /*<<< orphan*/ * g_556 ; 
 int /*<<< orphan*/ *** g_61 ; 
 int /*<<< orphan*/  g_70 ; 
 int /*<<< orphan*/  g_78 ; 
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
    transparent_crc(g_23, "g_23", print_hash_value);
    transparent_crc(g_25, "g_25", print_hash_value);
    transparent_crc(g_34, "g_34", print_hash_value);
    transparent_crc(g_42.f2, "g_42.f2", print_hash_value);
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 6; j++)
        {
            for (k = 0; k < 4; k++)
            {
                transparent_crc(g_61[i][j][k], "g_61[i][j][k]", print_hash_value);
                if (print_hash_value) printf("index = [%d][%d][%d]\n", i, j, k);

            }
        }
    }
    transparent_crc(g_70, "g_70", print_hash_value);
    transparent_crc(g_78, "g_78", print_hash_value);
    transparent_crc(g_117, "g_117", print_hash_value);
    transparent_crc(g_163.f0, "g_163.f0", print_hash_value);
    transparent_crc(g_163.f1, "g_163.f1", print_hash_value);
    for (i = 0; i < 7; i++)
    {
        transparent_crc(g_165[i], "g_165[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 8; j++)
        {
            for (k = 0; k < 3; k++)
            {
                transparent_crc(g_171[i][j][k], "g_171[i][j][k]", print_hash_value);
                if (print_hash_value) printf("index = [%d][%d][%d]\n", i, j, k);

            }
        }
    }
    transparent_crc(g_218, "g_218", print_hash_value);
    transparent_crc(g_234, "g_234", print_hash_value);
    transparent_crc(g_246, "g_246", print_hash_value);
    transparent_crc(g_255, "g_255", print_hash_value);
    transparent_crc(g_380, "g_380", print_hash_value);
    transparent_crc(g_387, "g_387", print_hash_value);
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 1; j++)
        {
            transparent_crc(g_405[i][j].f0, "g_405[i][j].f0", print_hash_value);
            transparent_crc(g_405[i][j].f1, "g_405[i][j].f1", print_hash_value);
            if (print_hash_value) printf("index = [%d][%d]\n", i, j);

        }
    }
    transparent_crc(g_471, "g_471", print_hash_value);
    transparent_crc(g_555, "g_555", print_hash_value);
    for (i = 0; i < 9; i++)
    {
        transparent_crc(g_556[i], "g_556[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    platform_main_end(crc32_context ^ 0xFFFFFFFFUL, print_hash_value);
    return 0;
}