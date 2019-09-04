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
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_3__ {int /*<<< orphan*/ * RemoteHostname; int /*<<< orphan*/  RemoteIP; } ;
typedef  TYPE_1__ SOCK ;

/* Variables and functions */
 int /*<<< orphan*/ * CopyStr (char*) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int GetHostName (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPToStr (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ IsEmptyStr (char*) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  Zero (char*,int) ; 
 int disable_gethostname_by_accept ; 

void AcceptInitEx(SOCK *s, bool no_lookup_hostname)
{
	char tmp[MAX_SIZE];
	// Validate arguments
	if (s == NULL)
	{
		return;
	}

	Zero(tmp, sizeof(tmp));

	if (disable_gethostname_by_accept == false && no_lookup_hostname == false)
	{
		if (GetHostName(tmp, sizeof(tmp), &s->RemoteIP) == false ||
			IsEmptyStr(tmp))
		{
			IPToStr(tmp, sizeof(tmp), &s->RemoteIP);
		}
	}
	else
	{
		IPToStr(tmp, sizeof(tmp), &s->RemoteIP);
	}

	if (s->RemoteHostname != NULL)
	{
		Free(s->RemoteHostname);
	}

	s->RemoteHostname = CopyStr(tmp);
}