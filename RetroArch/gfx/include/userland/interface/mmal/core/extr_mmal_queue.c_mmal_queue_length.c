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
struct TYPE_3__ {unsigned int length; } ;
typedef  TYPE_1__ MMAL_QUEUE_T ;

/* Variables and functions */

unsigned int mmal_queue_length(MMAL_QUEUE_T *queue)
{
	if(!queue) return 0;

	return queue->length;
}