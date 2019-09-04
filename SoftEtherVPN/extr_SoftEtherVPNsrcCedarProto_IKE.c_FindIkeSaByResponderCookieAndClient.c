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
typedef  scalar_t__ UINT64 ;
struct TYPE_4__ {int /*<<< orphan*/ * IkeClient; } ;
typedef  int /*<<< orphan*/  IKE_SERVER ;
typedef  TYPE_1__ IKE_SA ;
typedef  int /*<<< orphan*/  IKE_CLIENT ;

/* Variables and functions */
 TYPE_1__* FindIkeSaByResponderCookie (int /*<<< orphan*/ *,scalar_t__) ; 

IKE_SA *FindIkeSaByResponderCookieAndClient(IKE_SERVER *ike, UINT64 responder_cookie, IKE_CLIENT *c)
{
	IKE_SA *sa;
	// Validate arguments
	if (ike == NULL || responder_cookie == 0 || c == NULL)
	{
		return NULL;
	}

	sa = FindIkeSaByResponderCookie(ike, responder_cookie);
	if (sa == NULL)
	{
		return NULL;
	}

	if (sa->IkeClient != c)
	{
		return NULL;
	}

	return sa;
}