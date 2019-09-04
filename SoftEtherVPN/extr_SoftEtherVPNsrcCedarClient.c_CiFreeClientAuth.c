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
struct TYPE_4__ {int /*<<< orphan*/ * ClientK; int /*<<< orphan*/ * ClientX; } ;
typedef  TYPE_1__ CLIENT_AUTH ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeX (int /*<<< orphan*/ *) ; 

void CiFreeClientAuth(CLIENT_AUTH *auth)
{
	// Validate arguments
	if (auth == NULL)
	{
		return;
	}

	if (auth->ClientX != NULL)
	{
		FreeX(auth->ClientX);
	}
	if (auth->ClientK != NULL)
	{
		FreeK(auth->ClientK);
	}

	Free(auth);
}