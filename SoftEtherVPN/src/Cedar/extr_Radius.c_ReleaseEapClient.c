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
typedef  TYPE_1__ EAP_CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CleanupEapClient (TYPE_1__*) ; 
 scalar_t__ Release (int /*<<< orphan*/ ) ; 

void ReleaseEapClient(EAP_CLIENT *e)
{
	if (e == NULL)
	{
		return;
	}

	if (Release(e->Ref) == 0)
	{
		CleanupEapClient(e);
	}
}