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
struct snd_seq_pool {int /*<<< orphan*/  counter; struct snd_seq_event_cell* free; } ;
struct snd_seq_event_cell {struct snd_seq_event_cell* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void free_cell(struct snd_seq_pool *pool,
			     struct snd_seq_event_cell *cell)
{
	cell->next = pool->free;
	pool->free = cell;
	atomic_dec(&pool->counter);
}