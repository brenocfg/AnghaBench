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
typedef  int u8 ;
typedef  int u32 ;
struct ipz_queue {int toggle_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipz_qeit_eq_get_inc (struct ipz_queue*) ; 
 void* ipz_qeit_get (struct ipz_queue*) ; 

__attribute__((used)) static inline void *ipz_eqit_eq_get_inc_valid(struct ipz_queue *queue)
{
	void *ret = ipz_qeit_get(queue);
	u32 qe = *(u8 *)ret;
	if ((qe >> 7) != (queue->toggle_state & 1))
		return NULL;
	ipz_qeit_eq_get_inc(queue); /* this is a good one */
	return ret;
}