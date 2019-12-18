#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT64 ;
struct TYPE_8__ {scalar_t__ ResponderCookie; } ;
struct TYPE_7__ {int /*<<< orphan*/  IkeSaList; } ;
typedef  TYPE_1__ IKE_SERVER ;
typedef  TYPE_2__ IKE_SA ;

/* Variables and functions */
 TYPE_2__* Search (int /*<<< orphan*/ ,TYPE_2__*) ; 

IKE_SA *FindIkeSaByResponderCookie(IKE_SERVER *ike, UINT64 responder_cookie)
{
	IKE_SA t;
	// Validate arguments
	if (ike == NULL || responder_cookie == 0)
	{
		return NULL;
	}

	t.ResponderCookie = responder_cookie;

	return Search(ike->IkeSaList, &t);
}