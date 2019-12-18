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
struct mm_struct {void* faultstamp; scalar_t__ token_priority; int last_interval; } ;

/* Variables and functions */
 void* global_faults ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  spin_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swap_token_lock ; 
 struct mm_struct* swap_token_mm ; 

void grab_swap_token(struct mm_struct *mm)
{
	int current_interval;

	global_faults++;

	current_interval = global_faults - mm->faultstamp;

	if (!spin_trylock(&swap_token_lock))
		return;

	/* First come first served */
	if (swap_token_mm == NULL) {
		mm->token_priority = mm->token_priority + 2;
		swap_token_mm = mm;
		goto out;
	}

	if (mm != swap_token_mm) {
		if (current_interval < mm->last_interval)
			mm->token_priority++;
		else {
			if (likely(mm->token_priority > 0))
				mm->token_priority--;
		}
		/* Check if we deserve the token */
		if (mm->token_priority > swap_token_mm->token_priority) {
			mm->token_priority += 2;
			swap_token_mm = mm;
		}
	} else {
		/* Token holder came in again! */
		mm->token_priority += 2;
	}

out:
	mm->faultstamp = global_faults;
	mm->last_interval = current_interval;
	spin_unlock(&swap_token_lock);
}