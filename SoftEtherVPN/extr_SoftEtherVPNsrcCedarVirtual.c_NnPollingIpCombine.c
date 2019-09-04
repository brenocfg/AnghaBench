#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_12__ {scalar_t__ Expire; } ;
struct TYPE_11__ {int /*<<< orphan*/ * IpCombine; TYPE_1__* v; } ;
struct TYPE_10__ {scalar_t__ Now; } ;
typedef  TYPE_2__ NATIVE_NAT ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_3__ IP_COMBINE ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_3__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NnFreeIpCombine (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 

void NnPollingIpCombine(NATIVE_NAT *t)
{
	LIST *o;
	UINT i;
	// Validate arguments
	if (t == NULL)
	{
		return;
	}

	// Discard the old combining object
	o = NULL;
	for (i = 0;i < LIST_NUM(t->IpCombine);i++)
	{
		IP_COMBINE *c = LIST_DATA(t->IpCombine, i);

		if (c->Expire < t->v->Now)
		{
			if (o == NULL)
			{
				o = NewListFast(NULL);
			}
			Add(o, c);
		}
	}

	if (o != NULL)
	{
		for (i = 0;i < LIST_NUM(o);i++)
		{
			IP_COMBINE *c = LIST_DATA(o, i);

			// Remove from the list
			Delete(t->IpCombine, c);

			// Release the memory
			NnFreeIpCombine(t, c);
		}
		ReleaseList(o);
	}
}