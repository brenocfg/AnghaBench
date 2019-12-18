#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* start; struct TYPE_4__* next; } ;
typedef  TYPE_1__ BLOCK ;

/* Variables and functions */
 TYPE_1__* alloc_list ; 

__attribute__((used)) static BLOCK *find_region( void *addr )
{
	BLOCK *p;

	for( p = alloc_list; p; p = p->next ) {
		if (p->start == addr)
			return( p );
		if (p->start > addr)
			break;
	}
	return( NULL );
}