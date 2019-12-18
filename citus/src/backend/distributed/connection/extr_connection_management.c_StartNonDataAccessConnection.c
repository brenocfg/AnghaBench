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
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  MultiConnection ;

/* Variables and functions */
 scalar_t__ ConnectionUsedForAnyPlacements (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FORCE_NEW_CONNECTION ; 
 int /*<<< orphan*/ * StartNodeConnection (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

MultiConnection *
StartNonDataAccessConnection(const char *hostname, int32 port)
{
	uint32 flags = 0;
	MultiConnection *connection = StartNodeConnection(flags, hostname, port);

	if (ConnectionUsedForAnyPlacements(connection))
	{
		flags = FORCE_NEW_CONNECTION;

		connection = StartNodeConnection(flags, hostname, port);
	}

	return connection;
}