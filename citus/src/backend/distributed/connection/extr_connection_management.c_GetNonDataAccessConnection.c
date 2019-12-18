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
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  MultiConnection ;

/* Variables and functions */
 int /*<<< orphan*/  FinishConnectionEstablishment (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * StartNonDataAccessConnection (char const*,int /*<<< orphan*/ ) ; 

MultiConnection *
GetNonDataAccessConnection(const char *hostname, int32 port)
{
	MultiConnection *connection;

	connection = StartNonDataAccessConnection(hostname, port);

	FinishConnectionEstablishment(connection);

	return connection;
}