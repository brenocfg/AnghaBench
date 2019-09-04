#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ Now; int /*<<< orphan*/ * IpCombine; } ;
typedef  TYPE_1__ VH ;
typedef  scalar_t__ UINT ;
struct TYPE_10__ {scalar_t__ Expire; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_2__ IP_COMBINE ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  FreeIpCombine (TYPE_1__*,TYPE_2__*) ; 
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 

void PollingIpCombine(VH *v)
{
	LIST *o;
	UINT i;
	// Validate arguments
	if (v == NULL)
	{
		return;
	}

	// Discard the old combining object
	o = NULL;
	for (i = 0;i < LIST_NUM(v->IpCombine);i++)
	{
		IP_COMBINE *c = LIST_DATA(v->IpCombine, i);

		if (c->Expire < v->Now)
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
			Delete(v->IpCombine, c);

			// Release the memory
			FreeIpCombine(v, c);
		}
		ReleaseList(o);
	}
}