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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  lwp_queue ;
typedef  int /*<<< orphan*/  lwp_node ;

/* Variables and functions */
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * __lwp_queue_firstnodeI (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_queue_isempty (int /*<<< orphan*/ *) ; 

lwp_node* __lwp_queue_get(lwp_queue *queue)
{
	u32 level;
	lwp_node *ret = NULL;

	_CPU_ISR_Disable(level);
	if(!__lwp_queue_isempty(queue)) {
		ret	 = __lwp_queue_firstnodeI(queue);
	}
	_CPU_ISR_Restore(level);
	return ret;
}