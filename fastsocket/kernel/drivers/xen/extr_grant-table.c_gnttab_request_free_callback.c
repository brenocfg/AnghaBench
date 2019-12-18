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
typedef  int /*<<< orphan*/  u16 ;
struct gnttab_free_callback {void (* fn ) (void*) ;struct gnttab_free_callback* next; int /*<<< orphan*/  count; void* arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_free_callbacks () ; 
 struct gnttab_free_callback* gnttab_free_callback_list ; 
 int /*<<< orphan*/  gnttab_list_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void gnttab_request_free_callback(struct gnttab_free_callback *callback,
				  void (*fn)(void *), void *arg, u16 count)
{
	unsigned long flags;
	spin_lock_irqsave(&gnttab_list_lock, flags);
	if (callback->next)
		goto out;
	callback->fn = fn;
	callback->arg = arg;
	callback->count = count;
	callback->next = gnttab_free_callback_list;
	gnttab_free_callback_list = callback;
	check_free_callbacks();
out:
	spin_unlock_irqrestore(&gnttab_list_lock, flags);
}