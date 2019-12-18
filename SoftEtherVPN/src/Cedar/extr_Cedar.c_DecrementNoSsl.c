#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_7__ {int /*<<< orphan*/  NonSslList; } ;
struct TYPE_6__ {scalar_t__ Count; } ;
typedef  TYPE_1__ NON_SSL ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_2__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 TYPE_1__* SearchNoSslList (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void DecrementNoSsl(CEDAR *c, IP *ip, UINT num_dec)
{
	// Validate arguments
	if (c == NULL || ip == NULL)
	{
		return;
	}

	LockList(c->NonSslList);
	{
		NON_SSL *n = SearchNoSslList(c, ip);

		if (n != NULL)
		{
			if (n->Count >= num_dec)
			{
				n->Count -= num_dec;
			}
		}
	}
	UnlockList(c->NonSslList);
}