#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  SOCK_EVENT ;
typedef  int /*<<< orphan*/  INTERRUPT_MANAGER ;
typedef  int /*<<< orphan*/  CEDAR ;

/* Variables and functions */
 void* NewOpenVpnServer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool OvsInit(void **param, CEDAR *cedar, INTERRUPT_MANAGER *im, SOCK_EVENT *se)
{
	if (param == NULL || cedar == NULL || im == NULL || se == NULL)
	{
		return false;
	}

	*param = NewOpenVpnServer(cedar, im, se);

	return true;
}