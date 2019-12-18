#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_5__ {int /*<<< orphan*/  userName; TYPE_1__* connection; } ;
struct TYPE_4__ {scalar_t__ claimedExclusively; } ;
typedef  TYPE_1__ MultiConnection ;
typedef  TYPE_2__ ConnectionReference ;

/* Variables and functions */
 int FORCE_NEW_CONNECTION ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static bool
CanUseExistingConnection(uint32 flags, const char *userName,
						 ConnectionReference *connectionReference)
{
	MultiConnection *connection = connectionReference->connection;

	if (!connection)
	{
		/* if already closed connection obviously not usable */
		return false;
	}
	else if (connection->claimedExclusively)
	{
		/* already used */
		return false;
	}
	else if (flags & FORCE_NEW_CONNECTION)
	{
		/* no connection reuse desired */
		return false;
	}
	else if (strcmp(connectionReference->userName, userName) != 0)
	{
		/* connection for different user, check for conflict */
		return false;
	}
	else
	{
		return true;
	}
}