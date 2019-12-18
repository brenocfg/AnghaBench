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
struct ipz_queue {scalar_t__ current_q_offset; } ;

/* Variables and functions */
 void* ipz_qeit_get (struct ipz_queue*) ; 

__attribute__((used)) static inline void *ipz_qeit_reset(struct ipz_queue *queue)
{
	queue->current_q_offset = 0;
	return ipz_qeit_get(queue);
}