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
typedef  int uint32 ;
typedef  int /*<<< orphan*/  info ;
typedef  int /*<<< orphan*/  TaskMapKey ;
typedef  int /*<<< orphan*/  TaskMapEntry ;
struct TYPE_4__ {int keysize; int entrysize; int /*<<< orphan*/  hcxt; int /*<<< orphan*/  hash; } ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  TYPE_1__ HASHCTL ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int HASH_CONTEXT ; 
 int HASH_ELEM ; 
 int HASH_FUNCTION ; 
 int /*<<< orphan*/ * hash_create (char const*,int,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tag_hash ; 

__attribute__((used)) static HTAB *
TaskHashCreate(uint32 taskHashSize)
{
	HASHCTL info;
	const char *taskHashName = "Task Hash";
	int hashFlags = 0;
	HTAB *taskHash = NULL;

	/*
	 * Can't create a hashtable of size 0. Normally that shouldn't happen, but
	 * shard pruning currently can lead to this (Job with 0 Tasks). See #833.
	 */
	if (taskHashSize == 0)
	{
		taskHashSize = 2;
	}

	memset(&info, 0, sizeof(info));
	info.keysize = sizeof(TaskMapKey);
	info.entrysize = sizeof(TaskMapEntry);
	info.hash = tag_hash;
	info.hcxt = CurrentMemoryContext;
	hashFlags = (HASH_ELEM | HASH_FUNCTION | HASH_CONTEXT);

	taskHash = hash_create(taskHashName, taskHashSize, &info, hashFlags);

	return taskHash;
}