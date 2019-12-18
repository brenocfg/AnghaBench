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
 int /*<<< orphan*/ ** ClientConnectionArray ; 
 size_t INVALID_CONNECTION_ID ; 
 size_t MAX_CONNECTION_COUNT ; 

__attribute__((used)) static int32
AllocateConnectionId(void)
{
	int32 connectionId = INVALID_CONNECTION_ID;
	int32 connIndex = 0;

	/* allocate connectionId from connection pool */
	for (connIndex = 0; connIndex < MAX_CONNECTION_COUNT; connIndex++)
	{
		MultiConnection *connection = ClientConnectionArray[connIndex];
		if (connection == NULL)
		{
			connectionId = connIndex;
			break;
		}
	}

	return connectionId;
}