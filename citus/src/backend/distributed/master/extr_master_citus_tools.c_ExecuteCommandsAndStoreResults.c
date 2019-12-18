#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int int32 ;
struct TYPE_6__ {char* data; } ;
typedef  TYPE_1__* StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int ExecuteRemoteQueryOrCommand (char*,int,char*,TYPE_1__*) ; 

__attribute__((used)) static void
ExecuteCommandsAndStoreResults(StringInfo *nodeNameArray, int *nodePortArray,
							   StringInfo *commandStringArray, bool *statusArray,
							   StringInfo *resultStringArray, int commmandCount)
{
	int commandIndex = 0;
	for (commandIndex = 0; commandIndex < commmandCount; commandIndex++)
	{
		char *nodeName = nodeNameArray[commandIndex]->data;
		int32 nodePort = nodePortArray[commandIndex];
		bool success = false;
		char *queryString = commandStringArray[commandIndex]->data;
		StringInfo queryResultString = resultStringArray[commandIndex];

		success = ExecuteRemoteQueryOrCommand(nodeName, nodePort, queryString,
											  queryResultString);

		statusArray[commandIndex] = success;

		CHECK_FOR_INTERRUPTS();
	}
}