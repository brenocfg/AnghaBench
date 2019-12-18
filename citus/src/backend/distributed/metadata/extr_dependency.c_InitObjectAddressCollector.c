#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  info ;
struct TYPE_7__ {int keysize; int entrysize; int /*<<< orphan*/  hcxt; } ;
struct TYPE_6__ {void* visitedObjects; int /*<<< orphan*/ * dependencyList; void* dependencySet; } ;
typedef  TYPE_1__ ObjectAddressCollector ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  TYPE_2__ HASHCTL ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int HASH_BLOBS ; 
 int HASH_CONTEXT ; 
 int HASH_ELEM ; 
 void* hash_create (char*,int,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
InitObjectAddressCollector(ObjectAddressCollector *collector)
{
	int hashFlags = 0;
	HASHCTL info;

	memset(&info, 0, sizeof(info));
	info.keysize = sizeof(ObjectAddress);
	info.entrysize = sizeof(ObjectAddress);
	info.hcxt = CurrentMemoryContext;
	hashFlags = (HASH_ELEM | HASH_CONTEXT | HASH_BLOBS);

	collector->dependencySet = hash_create("dependency set", 128, &info, hashFlags);
	collector->dependencyList = NULL;

	collector->visitedObjects = hash_create("visited object set", 128, &info, hashFlags);
}