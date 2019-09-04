#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int crc32_context ; 
 int /*<<< orphan*/  crc32_gentab () ; 
 int /*<<< orphan*/  func_1 () ; 
 int /*<<< orphan*/ * g_1096 ; 
 int /*<<< orphan*/  g_1202 ; 
 int /*<<< orphan*/  g_124 ; 
 int /*<<< orphan*/  g_1250 ; 
 int /*<<< orphan*/  g_126 ; 
 int /*<<< orphan*/  g_131 ; 
 int /*<<< orphan*/  g_1312 ; 
 int /*<<< orphan*/ * g_138 ; 
 int /*<<< orphan*/  g_145 ; 
 int /*<<< orphan*/  g_1484 ; 
 int /*<<< orphan*/  g_1509 ; 
 int /*<<< orphan*/ *** g_1758 ; 
 int /*<<< orphan*/  g_1847 ; 
 int /*<<< orphan*/  g_1959 ; 
 int /*<<< orphan*/  g_2 ; 
 int /*<<< orphan*/ ** g_2057 ; 
 int /*<<< orphan*/  g_2156 ; 
 int /*<<< orphan*/ * g_2225 ; 
 int /*<<< orphan*/  g_2234 ; 
 int /*<<< orphan*/  g_2236 ; 
 int /*<<< orphan*/  g_2239 ; 
 int /*<<< orphan*/ ** g_2387 ; 
 int /*<<< orphan*/  g_2451 ; 
 int /*<<< orphan*/  g_2907 ; 
 int /*<<< orphan*/  g_3051 ; 
 int /*<<< orphan*/ * g_31 ; 
 int /*<<< orphan*/ * g_3207 ; 
 int /*<<< orphan*/  g_3271 ; 
 int /*<<< orphan*/  g_3299 ; 
 int /*<<< orphan*/  g_3397 ; 
 int /*<<< orphan*/  g_3398 ; 
 int /*<<< orphan*/  g_358 ; 
 int /*<<< orphan*/  g_36 ; 
 int /*<<< orphan*/  g_360 ; 
 int /*<<< orphan*/ ** g_408 ; 
 int /*<<< orphan*/  g_415 ; 
 int /*<<< orphan*/  g_436 ; 
 int /*<<< orphan*/  g_510 ; 
 int /*<<< orphan*/ * g_59 ; 
 int /*<<< orphan*/ *** g_60 ; 
 int /*<<< orphan*/  g_61 ; 
 int /*<<< orphan*/ * g_69 ; 
 int /*<<< orphan*/  g_775 ; 
 int /*<<< orphan*/  g_961 ; 
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
    for (i = 0; i < 1; i++)
    {
        transparent_crc(g_31[i], "g_31[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_36, "g_36", print_hash_value);
    for (i = 0; i < 9; i++)
    {
        transparent_crc(g_59[i], "g_59[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 5; j++)
        {
            for (k = 0; k < 4; k++)
            {
                transparent_crc(g_60[i][j][k], "g_60[i][j][k]", print_hash_value);
                if (print_hash_value) printf("index = [%d][%d][%d]\n", i, j, k);

            }
        }
    }
    transparent_crc(g_61, "g_61", print_hash_value);
    for (i = 0; i < 9; i++)
    {
        transparent_crc(g_69[i], "g_69[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_124, "g_124", print_hash_value);
    transparent_crc(g_126, "g_126", print_hash_value);
    transparent_crc(g_131, "g_131", print_hash_value);
    for (i = 0; i < 4; i++)
    {
        transparent_crc(g_138[i], "g_138[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_145, "g_145", print_hash_value);
    transparent_crc(g_358, "g_358", print_hash_value);
    transparent_crc(g_360, "g_360", print_hash_value);
    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 10; j++)
        {
            transparent_crc(g_408[i][j], "g_408[i][j]", print_hash_value);
            if (print_hash_value) printf("index = [%d][%d]\n", i, j);

        }
    }
    transparent_crc(g_415, "g_415", print_hash_value);
    transparent_crc(g_436, "g_436", print_hash_value);
    transparent_crc(g_510, "g_510", print_hash_value);
    transparent_crc(g_775, "g_775", print_hash_value);
    transparent_crc(g_961, "g_961", print_hash_value);
    for (i = 0; i < 1; i++)
    {
        transparent_crc(g_1096[i], "g_1096[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_1202, "g_1202", print_hash_value);
    transparent_crc(g_1250, "g_1250", print_hash_value);
    transparent_crc(g_1312, "g_1312", print_hash_value);
    transparent_crc(g_1484, "g_1484", print_hash_value);
    transparent_crc(g_1509, "g_1509", print_hash_value);
    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 9; j++)
        {
            for (k = 0; k < 3; k++)
            {
                transparent_crc(g_1758[i][j][k], "g_1758[i][j][k]", print_hash_value);
                if (print_hash_value) printf("index = [%d][%d][%d]\n", i, j, k);

            }
        }
    }
    transparent_crc(g_1847, "g_1847", print_hash_value);
    transparent_crc(g_1959, "g_1959", print_hash_value);
    for (i = 0; i < 7; i++)
    {
        for (j = 0; j < 8; j++)
        {
            transparent_crc(g_2057[i][j], "g_2057[i][j]", print_hash_value);
            if (print_hash_value) printf("index = [%d][%d]\n", i, j);

        }
    }
    transparent_crc(g_2156, "g_2156", print_hash_value);
    for (i = 0; i < 10; i++)
    {
        transparent_crc(g_2225[i], "g_2225[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_2234, "g_2234", print_hash_value);
    transparent_crc(g_2236, "g_2236", print_hash_value);
    transparent_crc(g_2239, "g_2239", print_hash_value);
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            transparent_crc(g_2387[i][j], "g_2387[i][j]", print_hash_value);
            if (print_hash_value) printf("index = [%d][%d]\n", i, j);

        }
    }
    transparent_crc(g_2451, "g_2451", print_hash_value);
    transparent_crc(g_2907, "g_2907", print_hash_value);
    transparent_crc(g_3051, "g_3051", print_hash_value);
    for (i = 0; i < 10; i++)
    {
        transparent_crc(g_3207[i], "g_3207[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_3271, "g_3271", print_hash_value);
    transparent_crc(g_3299, "g_3299", print_hash_value);
    transparent_crc(g_3397, "g_3397", print_hash_value);
    transparent_crc(g_3398, "g_3398", print_hash_value);
    platform_main_end(crc32_context ^ 0xFFFFFFFFUL, print_hash_value);
    return 0;
}