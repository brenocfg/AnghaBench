#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  f1; int /*<<< orphan*/  f0; } ;

/* Variables and functions */
 int crc32_context ; 
 int /*<<< orphan*/  crc32_gentab () ; 
 int /*<<< orphan*/  func_1 () ; 
 TYPE_1__*** g_7 ; 
 int /*<<< orphan*/  platform_main_begin () ; 
 int /*<<< orphan*/  platform_main_end (int,int) ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 
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
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 1; j++)
        {
            for (k = 0; k < 1; k++)
            {
                transparent_crc(g_7[i][j][k].f0, "g_7[i][j][k].f0", print_hash_value);
                transparent_crc(g_7[i][j][k].f1, "g_7[i][j][k].f1", print_hash_value);
                if (print_hash_value) printf("index = [%d][%d][%d]\n", i, j, k);
            }
        }
    }
    platform_main_end(crc32_context ^ 0xFFFFFFFFUL, print_hash_value);
    return 0;
}