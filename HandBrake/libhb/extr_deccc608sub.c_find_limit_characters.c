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
 int CC608_SCREEN_WIDTH ; 

__attribute__((used)) static void find_limit_characters(unsigned char *line, int *first_non_blank,
                                  int *last_non_blank)
{
    int i;

    *last_non_blank = -1;
    *first_non_blank = -1;
    for (i = 0; i < CC608_SCREEN_WIDTH; i++)
    {
        unsigned char c = line[i];
        if (c != ' ' && c != 0x89)
        {
            if (*first_non_blank == -1)
                *first_non_blank = i;
            *last_non_blank = i;
        }
    }
}