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
struct pullup_field {struct pullup_field* next; } ;

/* Variables and functions */

__attribute__((used)) static int pullup_queue_length( struct pullup_field * begin,
                                struct pullup_field * end )
{
    int count = 1;
    struct pullup_field * f;

    if( !begin || !end ) return 0;
    for( f = begin; f != end; f = f->next ) count++;
    return count;
}