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
typedef  int /*<<< orphan*/  info ;
struct TYPE_4__ {int keysize; int entrysize; int /*<<< orphan*/  hcxt; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  TYPE_1__ HASHCTL ;
typedef  int /*<<< orphan*/  CopyConnectionState ;

/* Variables and functions */
 int HASH_BLOBS ; 
 int HASH_CONTEXT ; 
 int HASH_ELEM ; 
 int /*<<< orphan*/ * hash_create (char*,int,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static HTAB *
CreateConnectionStateHash(MemoryContext memoryContext)
{
	HTAB *connectionStateHash = NULL;
	int hashFlags = 0;
	HASHCTL info;

	memset(&info, 0, sizeof(info));
	info.keysize = sizeof(int);
	info.entrysize = sizeof(CopyConnectionState);
	info.hcxt = memoryContext;
	hashFlags = (HASH_ELEM | HASH_CONTEXT | HASH_BLOBS);

	connectionStateHash = hash_create("Copy Connection State Hash", 128, &info,
									  hashFlags);

	return connectionStateHash;
}