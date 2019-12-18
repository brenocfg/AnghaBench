#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; struct TYPE_5__* next; } ;
typedef  TYPE_1__ BLOCK ;

/* Variables and functions */
 int BLOCK_FREE ; 
 int BLOCK_KMALLOCED ; 
 TYPE_1__* alloc_list ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

__attribute__((used)) static int remove_region( BLOCK *block )
{
	BLOCK **p;

	for( p = &alloc_list; *p; p = &((*p)->next) )
		if (*p == block) break;
	if (!*p)
		return( 0 );

	*p = block->next;
	if (block->flags & BLOCK_KMALLOCED)
		kfree( block );
	else
		block->flags |= BLOCK_FREE;
	return( 1 );
}