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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  QUEUE ;

/* Variables and functions */
 int /*<<< orphan*/ * Clone (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  InsertQueue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void InsertQueueInt(QUEUE *q, UINT value)
{
	UINT *p;
	// Validate arguments
	if (q == NULL)
	{
		return;
	}

	p = Clone(&value, sizeof(UINT));

	InsertQueue(q, p);
}