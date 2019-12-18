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
struct arg_hdr {int flag; } ;

/* Variables and functions */
 int ARG_TERMINATOR ; 

int arg_nullcheck(void * *argtable)
{
    struct arg_hdr * *table = (struct arg_hdr * *)argtable;
    int tabindex;
    /*printf("arg_nullcheck(%p)\n",argtable);*/

    if (!table)
        return 1;

    tabindex = 0;
    do
    {
        /*printf("argtable[%d]=%p\n",tabindex,argtable[tabindex]);*/
        if (!table[tabindex])
            return 1;
    } while(!(table[tabindex++]->flag & ARG_TERMINATOR));

    return 0;
}