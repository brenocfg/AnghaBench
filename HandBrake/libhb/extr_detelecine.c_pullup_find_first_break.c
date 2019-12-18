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
struct pullup_field {int breaks; struct pullup_field* next; } ;

/* Variables and functions */
 int PULLUP_BREAK_LEFT ; 
 int PULLUP_BREAK_RIGHT ; 

__attribute__((used)) static int pullup_find_first_break( struct pullup_field * f, int max )
{
    int i;
    for( i = 0; i < max; i++ )
    {
        if( f->breaks & PULLUP_BREAK_RIGHT ||
            f->next->breaks & PULLUP_BREAK_LEFT )
        {
            return i+1;
        }
        f = f->next;
    }
    return 0;
}