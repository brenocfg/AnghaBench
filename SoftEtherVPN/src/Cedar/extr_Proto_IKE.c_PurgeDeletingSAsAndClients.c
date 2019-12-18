#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_15__ {int /*<<< orphan*/ * ClientList; int /*<<< orphan*/ * IPsecSaList; int /*<<< orphan*/ * IkeSaList; } ;
struct TYPE_14__ {scalar_t__ Deleting; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ IPSECSA ;
typedef  TYPE_2__ IKE_SERVER ;
typedef  TYPE_1__ IKE_SA ;
typedef  TYPE_1__ IKE_CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PurgeIPsecSa (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  PurgeIkeClient (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  PurgeIkeSa (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 

void PurgeDeletingSAsAndClients(IKE_SERVER *ike)
{
	UINT i;
	LIST *o = NULL;
	// Validate arguments
	if (ike == NULL)
	{
		return;
	}

	for (i = 0;i < LIST_NUM(ike->IkeSaList);i++)
	{
		IKE_SA *sa = LIST_DATA(ike->IkeSaList, i);
		if (sa->Deleting)
		{
			if (o == NULL)
			{
				o = NewListFast(NULL);
			}

			Add(o, sa);
		}
	}

	for (i = 0;i < LIST_NUM(o);i++)
	{
		IKE_SA *sa = LIST_DATA(o, i);

		PurgeIkeSa(ike, sa);
	}

	ReleaseList(o);

	o = NULL;

	for (i = 0;i < LIST_NUM(ike->IPsecSaList);i++)
	{
		IPSECSA *sa = LIST_DATA(ike->IPsecSaList, i);
		if (sa->Deleting)
		{
			if (o == NULL)
			{
				o = NewListFast(NULL);
			}

			Add(o, sa);
		}
	}

	for (i = 0;i < LIST_NUM(o);i++)
	{
		IPSECSA *sa = LIST_DATA(o, i);

		PurgeIPsecSa(ike, sa);
	}

	ReleaseList(o);

	o = NULL;

	for (i = 0;i < LIST_NUM(ike->ClientList);i++)
	{
		IKE_CLIENT *c = LIST_DATA(ike->ClientList, i);
		if (c->Deleting)
		{
			if (o == NULL)
			{
				o = NewListFast(NULL);
			}

			Add(o, c);
		}
	}

	for (i = 0;i < LIST_NUM(o);i++)
	{
		IKE_CLIENT *c = LIST_DATA(o, i);

		PurgeIkeClient(ike, c);
	}

	ReleaseList(o);
}