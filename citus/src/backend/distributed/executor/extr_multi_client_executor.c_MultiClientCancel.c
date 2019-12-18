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
typedef  size_t int32 ;
typedef  int /*<<< orphan*/  MultiConnection ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ ** ClientConnectionArray ; 
 size_t INVALID_CONNECTION_ID ; 
 int SendCancelationRequest (int /*<<< orphan*/ *) ; 

bool
MultiClientCancel(int32 connectionId)
{
	MultiConnection *connection = NULL;
	bool canceled = true;

	Assert(connectionId != INVALID_CONNECTION_ID);
	connection = ClientConnectionArray[connectionId];
	Assert(connection != NULL);

	canceled = SendCancelationRequest(connection);

	return canceled;
}