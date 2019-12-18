#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_9__ {TYPE_2__* last; int /*<<< orphan*/ * perm_null; } ;
typedef  TYPE_1__ lwp_queue ;
struct TYPE_10__ {struct TYPE_10__* next; struct TYPE_10__* prev; } ;
typedef  TYPE_2__ lwp_node ;

/* Variables and functions */
 TYPE_2__* __lwp_queue_head (TYPE_1__*) ; 
 TYPE_2__* __lwp_queue_tail (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,TYPE_1__*,void*,int,int) ; 

void __lwp_queue_initialize(lwp_queue *queue,void *start_addr,u32 num_nodes,u32 node_size)
{
	u32 count;
	lwp_node *curr;
	lwp_node *next;

#ifdef _LWPQ_DEBUG
	printf("__lwp_queue_initialize(%p,%p,%d,%d)\n",queue,start_addr,num_nodes,node_size);
#endif
	count = num_nodes;
	curr = __lwp_queue_head(queue);
	queue->perm_null = NULL;
	next = (lwp_node*)start_addr;

	while(count--) {
		curr->next = next;
		next->prev = curr;
		curr = next;
		next = (lwp_node*)(((void*)next)+node_size);
	}
	curr->next = __lwp_queue_tail(queue);
	queue->last = curr;
}