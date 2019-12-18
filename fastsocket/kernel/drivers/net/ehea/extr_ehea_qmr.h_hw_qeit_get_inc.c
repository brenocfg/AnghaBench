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
struct hw_queue {int dummy; } ;

/* Variables and functions */
 void* hw_qeit_get (struct hw_queue*) ; 
 int /*<<< orphan*/  hw_qeit_inc (struct hw_queue*) ; 

__attribute__((used)) static inline void *hw_qeit_get_inc(struct hw_queue *queue)
{
	void *retvalue = hw_qeit_get(queue);
	hw_qeit_inc(queue);
	return retvalue;
}