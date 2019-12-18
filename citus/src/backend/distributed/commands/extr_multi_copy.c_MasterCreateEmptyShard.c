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
typedef  int /*<<< orphan*/  int64 ;

/* Variables and functions */
 int /*<<< orphan*/  CreateEmptyShard (char*) ; 
 int /*<<< orphan*/  RemoteCreateEmptyShard (char*) ; 
 int /*<<< orphan*/ * masterConnection ; 

__attribute__((used)) static int64
MasterCreateEmptyShard(char *relationName)
{
	int64 shardId = 0;
	if (masterConnection == NULL)
	{
		shardId = CreateEmptyShard(relationName);
	}
	else
	{
		shardId = RemoteCreateEmptyShard(relationName);
	}

	return shardId;
}