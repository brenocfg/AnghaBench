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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int /*<<< orphan*/  num_item; } ;
typedef  TYPE_1__ QUEUE ;

/* Variables and functions */

UINT GetQueueNum(QUEUE *q)
{
	// Validate arguments
	if (q == NULL)
	{
		return 0;
	}

	return q->num_item;
}