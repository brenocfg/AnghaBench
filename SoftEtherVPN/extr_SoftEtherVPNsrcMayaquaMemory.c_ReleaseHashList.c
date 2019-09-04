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
typedef  TYPE_1__ HASH_LIST ;

/* Variables and functions */
 int /*<<< orphan*/  CleanupHashList (TYPE_1__*) ; 
 scalar_t__ Release (int /*<<< orphan*/ ) ; 

void ReleaseHashList(HASH_LIST *h)
{
	// Validate arguments
	if (h == NULL)
	{
		return;
	}

	if (Release(h->Ref) == 0)
	{
		CleanupHashList(h);
	}
}