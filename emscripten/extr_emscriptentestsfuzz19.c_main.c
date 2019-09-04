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
 int /*<<< orphan*/  g_1055 ; 
 int /*<<< orphan*/  g_1099 ; 
 int /*<<< orphan*/  g_1132 ; 
 int /*<<< orphan*/  g_1189 ; 
 int /*<<< orphan*/ *** g_1254 ; 
 int /*<<< orphan*/  g_1285 ; 
 int /*<<< orphan*/  g_1298 ; 
 int /*<<< orphan*/  g_1333 ; 
 int /*<<< orphan*/  g_1334 ; 
 int /*<<< orphan*/ * g_14 ; 
 int /*<<< orphan*/  g_140 ; 
 int /*<<< orphan*/  g_15 ; 
 int /*<<< orphan*/  g_1509 ; 
 int /*<<< orphan*/  g_1766 ; 
 int /*<<< orphan*/  g_1776 ; 
 int /*<<< orphan*/ *** g_1782 ; 
 int /*<<< orphan*/  g_1857 ; 
 int /*<<< orphan*/  g_1961 ; 
 int /*<<< orphan*/ ** g_2 ; 
 int /*<<< orphan*/  g_2067 ; 
 int /*<<< orphan*/ * g_2147 ; 
 int /*<<< orphan*/  g_2148 ; 
 int /*<<< orphan*/  g_2207 ; 
 int /*<<< orphan*/  g_251 ; 
 int /*<<< orphan*/  g_255 ; 
 int /*<<< orphan*/  g_290 ; 
 int /*<<< orphan*/ * g_294 ; 
 int /*<<< orphan*/ * g_297 ; 
 int /*<<< orphan*/  g_3 ; 
 int /*<<< orphan*/  g_320 ; 
 int /*<<< orphan*/  g_34 ; 
 int /*<<< orphan*/  g_347 ; 
 int /*<<< orphan*/  g_36 ; 
 int /*<<< orphan*/ * g_40 ; 
 int /*<<< orphan*/  g_419 ; 
 int /*<<< orphan*/  g_44 ; 
 int /*<<< orphan*/  g_46 ; 
 int /*<<< orphan*/  g_477 ; 
 int /*<<< orphan*/ *** g_51 ; 
 int /*<<< orphan*/  g_52 ; 
 int /*<<< orphan*/  g_56 ; 
 int /*<<< orphan*/ * g_705 ; 
 int /*<<< orphan*/  g_969 ; 
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
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 1; j++)
        {
            transparent_crc(g_2[i][j], "g_2[i][j]", print_hash_value);
            if (print_hash_value) printf("index = [%d][%d]\n", i, j);

        }
    }
    transparent_crc(g_3, "g_3", print_hash_value);
    for (i = 0; i < 6; i++)
    {
        transparent_crc(g_14[i], "g_14[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_15, "g_15", print_hash_value);
    transparent_crc(g_34, "g_34", print_hash_value);
    transparent_crc(g_36, "g_36", print_hash_value);
    for (i = 0; i < 7; i++)
    {
        transparent_crc(g_40[i], "g_40[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_44, "g_44", print_hash_value);
    transparent_crc(g_46, "g_46", print_hash_value);
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 8; j++)
        {
            for (k = 0; k < 3; k++)
            {
                transparent_crc(g_51[i][j][k], "g_51[i][j][k]", print_hash_value);
                if (print_hash_value) printf("index = [%d][%d][%d]\n", i, j, k);

            }
        }
    }
    transparent_crc(g_52, "g_52", print_hash_value);
    transparent_crc(g_56, "g_56", print_hash_value);
    transparent_crc(g_140, "g_140", print_hash_value);
    transparent_crc(g_251, "g_251", print_hash_value);
    transparent_crc(g_255, "g_255", print_hash_value);
    transparent_crc(g_290, "g_290", print_hash_value);
    for (i = 0; i < 5; i++)
    {
        transparent_crc(g_294[i], "g_294[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    for (i = 0; i < 2; i++)
    {
        transparent_crc(g_297[i], "g_297[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_320, "g_320", print_hash_value);
    transparent_crc(g_347, "g_347", print_hash_value);
    transparent_crc(g_419, "g_419", print_hash_value);
    transparent_crc(g_477, "g_477", print_hash_value);
    for (i = 0; i < 6; i++)
    {
        transparent_crc(g_705[i], "g_705[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_969, "g_969", print_hash_value);
    transparent_crc(g_1055, "g_1055", print_hash_value);
    transparent_crc(g_1099, "g_1099", print_hash_value);
    transparent_crc(g_1132, "g_1132", print_hash_value);
    transparent_crc(g_1189, "g_1189", print_hash_value);
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 1; j++)
        {
            for (k = 0; k < 8; k++)
            {
                transparent_crc(g_1254[i][j][k], "g_1254[i][j][k]", print_hash_value);
                if (print_hash_value) printf("index = [%d][%d][%d]\n", i, j, k);

            }
        }
    }
    transparent_crc(g_1285, "g_1285", print_hash_value);
    transparent_crc(g_1298, "g_1298", print_hash_value);
    transparent_crc(g_1333, "g_1333", print_hash_value);
    transparent_crc(g_1334, "g_1334", print_hash_value);
    transparent_crc(g_1509, "g_1509", print_hash_value);
    transparent_crc(g_1766, "g_1766", print_hash_value);
    transparent_crc(g_1776, "g_1776", print_hash_value);
    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 8; j++)
        {
            for (k = 0; k < 5; k++)
            {
                transparent_crc(g_1782[i][j][k], "g_1782[i][j][k]", print_hash_value);
                if (print_hash_value) printf("index = [%d][%d][%d]\n", i, j, k);

            }
        }
    }
    transparent_crc(g_1857, "g_1857", print_hash_value);
    transparent_crc(g_1961, "g_1961", print_hash_value);
    transparent_crc(g_2067, "g_2067", print_hash_value);
    for (i = 0; i < 10; i++)
    {
        transparent_crc(g_2147[i], "g_2147[i]", print_hash_value);
        if (print_hash_value) printf("index = [%d]\n", i);

    }
    transparent_crc(g_2148, "g_2148", print_hash_value);
    transparent_crc(g_2207, "g_2207", print_hash_value);
    platform_main_end(crc32_context ^ 0xFFFFFFFFUL, print_hash_value);
    return 0;
}