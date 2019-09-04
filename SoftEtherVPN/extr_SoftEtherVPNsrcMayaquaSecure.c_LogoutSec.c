#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int LoginFlag; int /*<<< orphan*/  SessionId; TYPE_1__* Api; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* C_Logout ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ SECURE ;

/* Variables and functions */
 int /*<<< orphan*/  EraseEnumSecObjectCache (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void LogoutSec(SECURE *sec)
{
	// Validate arguments
	if (sec == NULL)
	{
		return;
	}
	if (sec->LoginFlag == false)
	{
		return;
	}

	// Log-out
	sec->Api->C_Logout(sec->SessionId);

	// Clear Cache
	EraseEnumSecObjectCache(sec);

	sec->LoginFlag = false;
}