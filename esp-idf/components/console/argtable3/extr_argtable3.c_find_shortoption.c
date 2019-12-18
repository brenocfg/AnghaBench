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
struct arg_hdr {int flag; scalar_t__ shortopts; } ;

/* Variables and functions */
 int ARG_TERMINATOR ; 
 scalar_t__ strchr (scalar_t__,char) ; 

__attribute__((used)) static
int find_shortoption(struct arg_hdr * *table, char shortopt)
{
    int tabindex;
    for(tabindex = 0; !(table[tabindex]->flag & ARG_TERMINATOR); tabindex++)
    {
        if (table[tabindex]->shortopts &&
            strchr(table[tabindex]->shortopts, shortopt))
            return tabindex;
    }
    return -1;
}