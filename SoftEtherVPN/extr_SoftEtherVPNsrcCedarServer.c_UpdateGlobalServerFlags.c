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
struct TYPE_3__ {int /*<<< orphan*/  Cedar; } ;
typedef  TYPE_1__ SERVER ;
typedef  int /*<<< orphan*/  CAPSLIST ;

/* Variables and functions */
 int /*<<< orphan*/  GSF_DISABLE_AC ; 
 int /*<<< orphan*/  GSF_DISABLE_CERT_AUTH ; 
 int /*<<< orphan*/  GSF_DISABLE_DEEP_LOGGING ; 
 int /*<<< orphan*/  GSF_DISABLE_PUSH_ROUTE ; 
 int /*<<< orphan*/  GSF_DISABLE_RADIUS_AUTH ; 
 int /*<<< orphan*/  GSF_DISABLE_SYSLOG ; 
 int /*<<< orphan*/  SetGlobalServerFlag (int /*<<< orphan*/ ,int) ; 
 int SiIsEnterpriseFunctionsRestrictedOnOpenSource (int /*<<< orphan*/ ) ; 

void UpdateGlobalServerFlags(SERVER *s, CAPSLIST *t)
{
	bool is_restricted = false;
	// Validate arguments
	if (s == NULL || t == NULL)
	{
		return;
	}

	is_restricted = SiIsEnterpriseFunctionsRestrictedOnOpenSource(s->Cedar);

	SetGlobalServerFlag(GSF_DISABLE_PUSH_ROUTE, is_restricted);
	SetGlobalServerFlag(GSF_DISABLE_RADIUS_AUTH, is_restricted);
	SetGlobalServerFlag(GSF_DISABLE_CERT_AUTH, is_restricted);
	SetGlobalServerFlag(GSF_DISABLE_DEEP_LOGGING, is_restricted);
	SetGlobalServerFlag(GSF_DISABLE_AC, is_restricted);
	SetGlobalServerFlag(GSF_DISABLE_SYSLOG, is_restricted);
}