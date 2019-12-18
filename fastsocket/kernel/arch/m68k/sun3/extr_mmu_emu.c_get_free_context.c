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
struct mm_struct {int dummy; } ;

/* Variables and functions */
 unsigned long CONTEXTS_NUM ; 
 int /*<<< orphan*/  clear_context (unsigned long) ; 
 struct mm_struct** ctx_alloc ; 
 int /*<<< orphan*/  ctx_avail ; 
 int /*<<< orphan*/  panic (char*) ; 

unsigned long get_free_context(struct mm_struct *mm)
{
	unsigned long new = 1;
	static unsigned char next_to_die = 1;

	if(!ctx_avail) {
		/* kill someone to get our context */
		new = next_to_die;
		clear_context(new);
		next_to_die = (next_to_die + 1) & 0x7;
		if(!next_to_die)
			next_to_die++;
	} else {
		while(new < CONTEXTS_NUM) {
			if(ctx_alloc[new])
				new++;
			else
				break;
		}
		// check to make sure one was really free...
		if(new == CONTEXTS_NUM)
			panic("get_free_context: failed to find free context");
	}

	ctx_alloc[new] = mm;
	ctx_avail--;

	return new;
}