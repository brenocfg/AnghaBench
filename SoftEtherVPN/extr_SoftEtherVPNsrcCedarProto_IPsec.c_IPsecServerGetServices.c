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
struct TYPE_4__ {int /*<<< orphan*/  LockSettings; int /*<<< orphan*/  Services; } ;
typedef  int /*<<< orphan*/  IPSEC_SERVICES ;
typedef  TYPE_1__ IPSEC_SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IPsecNormalizeServiceSetting (TYPE_1__*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

void IPsecServerGetServices(IPSEC_SERVER *s, IPSEC_SERVICES *sl)
{
	// Validate arguments
	if (s == NULL || sl == NULL)
	{
		return;
	}

	Lock(s->LockSettings);
	{
		IPsecNormalizeServiceSetting(s);

		Copy(sl, &s->Services, sizeof(IPSEC_SERVICES));
	}
	Unlock(s->LockSettings);
}