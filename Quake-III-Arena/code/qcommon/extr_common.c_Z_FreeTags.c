#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int tag; struct TYPE_5__* next; } ;
struct TYPE_6__ {TYPE_1__* rover; TYPE_1__ blocklist; } ;
typedef  TYPE_2__ memzone_t ;

/* Variables and functions */
 int TAG_SMALL ; 
 int /*<<< orphan*/  Z_Free (void*) ; 
 TYPE_2__* mainzone ; 
 TYPE_2__* smallzone ; 

void Z_FreeTags( int tag ) {
	int			count;
	memzone_t	*zone;

	if ( tag == TAG_SMALL ) {
		zone = smallzone;
	}
	else {
		zone = mainzone;
	}
	count = 0;
	// use the rover as our pointer, because
	// Z_Free automatically adjusts it
	zone->rover = zone->blocklist.next;
	do {
		if ( zone->rover->tag == tag ) {
			count++;
			Z_Free( (void *)(zone->rover + 1) );
			continue;
		}
		zone->rover = zone->rover->next;
	} while ( zone->rover != &zone->blocklist );
}