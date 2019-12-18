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
struct arg_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct arg_hdr*) ; 

void arg_freetable(void * *argtable, size_t n)
{
    struct arg_hdr * *table = (struct arg_hdr * *)argtable;
    size_t tabindex = 0;
    /*printf("arg_freetable(%p)\n",argtable);*/
    for (tabindex = 0; tabindex < n; tabindex++)
    {
        if (table[tabindex] == NULL)
            continue;

        free(table[tabindex]);
        table[tabindex] = NULL;
    };
}