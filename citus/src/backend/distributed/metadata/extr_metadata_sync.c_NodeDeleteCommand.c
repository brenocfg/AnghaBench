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
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_4__ {char* data; } ;
typedef  TYPE_1__* StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* makeStringInfo () ; 

char *
NodeDeleteCommand(uint32 nodeId)
{
	StringInfo nodeDeleteCommand = makeStringInfo();

	appendStringInfo(nodeDeleteCommand,
					 "DELETE FROM pg_dist_node "
					 "WHERE nodeid = %u", nodeId);

	return nodeDeleteCommand->data;
}