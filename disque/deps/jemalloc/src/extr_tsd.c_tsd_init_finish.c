#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  blocks; } ;
typedef  TYPE_1__ tsd_init_head_t ;
typedef  int /*<<< orphan*/  tsd_init_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
tsd_init_finish(tsd_init_head_t *head, tsd_init_block_t *block)
{

	malloc_mutex_lock(&head->lock);
	ql_remove(&head->blocks, block, link);
	malloc_mutex_unlock(&head->lock);
}