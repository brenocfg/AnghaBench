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
typedef  void irda_queue_t ;
struct TYPE_5__ {int /*<<< orphan*/  hb_spinlock; void* hb_current; } ;
typedef  TYPE_1__ hashbin_t ;

/* Variables and functions */
 scalar_t__ hashbin_find (TYPE_1__*,long,char const*) ; 
 void* hashbin_get_next (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void* hashbin_find_next( hashbin_t* hashbin, long hashv, const char* name,
			 void ** pnext)
{
	unsigned long flags = 0;
	irda_queue_t* entry;

	/* Synchronize */
	spin_lock_irqsave(&hashbin->hb_spinlock, flags);

	/*
	 * Search for current entry
	 * This allow to check if the current item is still in the
	 * hashbin or has been removed.
	 */
	entry = (irda_queue_t* ) hashbin_find( hashbin, hashv, name );

	/*
	 * Trick hashbin_get_next() to return what we want
	 */
	if(entry) {
		hashbin->hb_current = entry;
		*pnext = hashbin_get_next( hashbin );
	} else
		*pnext = NULL;

	/* Release lock */
	spin_unlock_irqrestore(&hashbin->hb_spinlock, flags);

	return entry;
}