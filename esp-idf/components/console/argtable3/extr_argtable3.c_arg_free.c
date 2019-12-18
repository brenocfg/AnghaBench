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
 int /*<<< orphan*/  free (struct arg_hdr*) ; 

void arg_free(void * *argtable)
{
    struct arg_hdr * *table = (struct arg_hdr * *)argtable;
    int tabindex = 0;
    int flag;
    /*printf("arg_free(%p)\n",argtable);*/
    do
    {
        /*
           if we encounter a NULL entry then somewhat incorrectly we presume
           we have come to the end of the array. It isnt strictly true because
           an intermediate entry could be NULL with other non-NULL entries to follow.
           The subsequent argtable entries would then not be freed as they should.
         */
        if (table[tabindex] == NULL)
            break;

        flag = table[tabindex]->flag;
        free(table[tabindex]);
        table[tabindex++] = NULL;

    } while(!(flag & ARG_TERMINATOR));
}