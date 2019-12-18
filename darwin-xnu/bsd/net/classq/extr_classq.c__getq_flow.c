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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  class_queue_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 void* _getq_flow_or_scidx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void *
_getq_flow(class_queue_t *q, u_int32_t flow)
{
	return (_getq_flow_or_scidx(q, flow, TRUE));
}