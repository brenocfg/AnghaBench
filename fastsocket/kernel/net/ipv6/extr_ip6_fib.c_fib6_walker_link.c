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
struct fib6_walker_t {struct fib6_walker_t* next; struct fib6_walker_t* prev; } ;

/* Variables and functions */
 struct fib6_walker_t fib6_walker_list ; 
 int /*<<< orphan*/  fib6_walker_lock ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void fib6_walker_link(struct fib6_walker_t *w)
{
	write_lock_bh(&fib6_walker_lock);
	w->next = fib6_walker_list.next;
	w->prev = &fib6_walker_list;
	w->next->prev = w;
	w->prev->next = w;
	write_unlock_bh(&fib6_walker_lock);
}