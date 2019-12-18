#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  Ref; } ;
typedef  TYPE_1__ GETIP_THREAD_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  CleanupGetIPThreadParam (TYPE_1__*) ; 
 scalar_t__ Release (int /*<<< orphan*/ ) ; 

void ReleaseGetIPThreadParam(GETIP_THREAD_PARAM *p)
{
	// Validate arguments
	if (p == NULL)
	{
		return;
	}

	if (Release(p->Ref) == 0)
	{
		CleanupGetIPThreadParam(p);
	}
}