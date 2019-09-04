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
typedef  int /*<<< orphan*/  X ;
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * ServerK; int /*<<< orphan*/ * ServerX; } ;
typedef  int /*<<< orphan*/  K ;
typedef  TYPE_1__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/ * CloneK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CloneX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

void SetCedarCert(CEDAR *c, X *server_x, K *server_k)
{
	// Validate arguments
	if (server_x == NULL || server_k == NULL)
	{
		return;
	}

	Lock(c->lock);
	{
		if (c->ServerX != NULL)
		{
			FreeX(c->ServerX);
		}

		if (c->ServerK != NULL)
		{
			FreeK(c->ServerK);
		}

		c->ServerX = CloneX(server_x);
		c->ServerK = CloneK(server_k);
	}
	Unlock(c->lock);
}