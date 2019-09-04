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
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  Config; } ;
typedef  int /*<<< orphan*/  CLIENT_CONFIG ;
typedef  TYPE_1__ CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

bool CtGetClientConfig(CLIENT *c, CLIENT_CONFIG *o)
{
	// Validate arguments
	if (c == NULL || o == NULL)
	{
		return false;
	}

	Lock(c->lock);
	{
		Copy(o, &c->Config, sizeof(CLIENT_CONFIG));
	}
	Unlock(c->lock);

	return true;
}