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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  POLICY ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/ * PackGetPolicy (int /*<<< orphan*/ *) ; 
 int PackGetStr (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 

bool ParseWelcomeFromPack(PACK *p, char *session_name, UINT session_name_size,
						  char *connection_name, UINT connection_name_size,
						  POLICY **policy)
{
	// Validate arguments
	if (p == NULL || session_name == NULL || connection_name == NULL || policy == NULL)
	{
		return false;
	}

	// Session name
	if (PackGetStr(p, "session_name", session_name, session_name_size) == false)
	{
		return false;
	}

	// Connection name
	if (PackGetStr(p, "connection_name", connection_name, connection_name_size) == false)
	{
		return false;
	}

	// Policy
	*policy = PackGetPolicy(p);
	if (*policy == NULL)
	{
		return false;
	}

	return true;
}