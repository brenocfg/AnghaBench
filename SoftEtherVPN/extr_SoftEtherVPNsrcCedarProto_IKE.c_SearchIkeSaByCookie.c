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
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_7__ {scalar_t__ InitiatorCookie; scalar_t__ ResponderCookie; } ;
struct TYPE_6__ {int /*<<< orphan*/  IkeSaList; } ;
typedef  TYPE_1__ IKE_SERVER ;
typedef  TYPE_2__ IKE_SA ;

/* Variables and functions */
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 

IKE_SA *SearchIkeSaByCookie(IKE_SERVER *ike, UINT64 init_cookie, UINT64 resp_cookie)
{
	UINT i;
	// Validate arguments
	if (ike == NULL)
	{
		return NULL;
	}

	for (i = 0;i < LIST_NUM(ike->IkeSaList);i++)
	{
		IKE_SA *sa = LIST_DATA(ike->IkeSaList, i);

		if (sa->InitiatorCookie == init_cookie && sa->ResponderCookie == resp_cookie)
		{
			return sa;
		}
	}

	return NULL;
}