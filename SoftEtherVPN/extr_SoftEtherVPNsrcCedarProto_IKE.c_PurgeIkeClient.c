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
struct TYPE_12__ {int /*<<< orphan*/ * IkeClient; } ;
struct TYPE_11__ {int /*<<< orphan*/  ClientList; int /*<<< orphan*/  IPsecSaList; int /*<<< orphan*/  IkeSaList; } ;
struct TYPE_10__ {int /*<<< orphan*/ * IkeClient; } ;
typedef  TYPE_1__ IPSECSA ;
typedef  TYPE_2__ IKE_SERVER ;
typedef  TYPE_3__ IKE_SA ;
typedef  int /*<<< orphan*/  IKE_CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeIkeClient (TYPE_2__*,int /*<<< orphan*/ *) ; 
 void* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkIPsecSaAsDeleted (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  MarkIkeSaAsDeleted (TYPE_2__*,TYPE_3__*) ; 

void PurgeIkeClient(IKE_SERVER *ike, IKE_CLIENT *c)
{
	UINT i;
	// Validate arguments
	if (ike == NULL || c == NULL)
	{
		return;
	}

	// Delete all of IPsec SA and IKE SA that belong to this IKE Client
	for (i = 0;i < LIST_NUM(ike->IkeSaList);i++)
	{
		IKE_SA *sa = LIST_DATA(ike->IkeSaList, i);

		if (sa->IkeClient == c)
		{
			MarkIkeSaAsDeleted(ike, sa);
		}
	}
	for (i = 0;i < LIST_NUM(ike->IPsecSaList);i++)
	{
		IPSECSA *sa = LIST_DATA(ike->IPsecSaList, i);

		if (sa->IkeClient == c)
		{
			MarkIPsecSaAsDeleted(ike, sa);
		}
	}

	Delete(ike->ClientList, c);
	FreeIkeClient(ike, c);
}