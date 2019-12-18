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
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  FARM_TASK ;
typedef  int /*<<< orphan*/  FARM_MEMBER ;

/* Variables and functions */
 int /*<<< orphan*/ * SiFarmServPostTask (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SiFarmServWaitTask (int /*<<< orphan*/ *) ; 

PACK *SiExecTask(FARM_MEMBER *f, PACK *p)
{
	FARM_TASK *t;
	// Validate arguments
	if (f == NULL || p == NULL)
	{
		return NULL;
	}

	t = SiFarmServPostTask(f, p);
	if (t == NULL)
	{
		return NULL;
	}

	return SiFarmServWaitTask(t);
}