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
typedef  int /*<<< orphan*/  VH ;
typedef  int /*<<< orphan*/  THREAD ;

/* Variables and functions */
 int /*<<< orphan*/  NatThreadMain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NoticeThreadInit (int /*<<< orphan*/ *) ; 

void NatThread(THREAD *t, void *param)
{
	// Validate arguments
	if (t == NULL || param == NULL)
	{
		return;
	}

	// Notify the initialization completion
	NoticeThreadInit(t);

	NatThreadMain((VH *)param);
}