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
struct TYPE_5__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  buf_size; int /*<<< orphan*/  areas; } ;
typedef  TYPE_1__ debug_info_t ;
typedef  int /*<<< orphan*/  debug_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_DATA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_active ; 
 scalar_t__ debug_critical ; 
 int /*<<< orphan*/  debug_finish_entry (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_active_entry (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_trylock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

debug_entry_t*
debug_event_common(debug_info_t * id, int level, const void *buf, int len)
{
	unsigned long flags;
	debug_entry_t *active;

	if (!debug_active || !id->areas)
		return NULL;
	if (debug_critical) {
		if (!spin_trylock_irqsave(&id->lock, flags))
			return NULL;
	} else
		spin_lock_irqsave(&id->lock, flags);
	active = get_active_entry(id);
	memset(DEBUG_DATA(active), 0, id->buf_size);
	memcpy(DEBUG_DATA(active), buf, min(len, id->buf_size));
	debug_finish_entry(id, active, level, 0);
	spin_unlock_irqrestore(&id->lock, flags);

	return active;
}