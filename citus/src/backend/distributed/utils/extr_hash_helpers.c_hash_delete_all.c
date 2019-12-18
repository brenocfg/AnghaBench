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
typedef  int /*<<< orphan*/  HTAB ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  HASH_REMOVE ; 
 int /*<<< orphan*/  hash_search (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* hash_seq_search (int /*<<< orphan*/ *) ; 

void
hash_delete_all(HTAB *htab)
{
	HASH_SEQ_STATUS status;
	void *entry = NULL;

	hash_seq_init(&status, htab);
	while ((entry = hash_seq_search(&status)) != 0)
	{
		bool found = false;

		hash_search(htab, entry, HASH_REMOVE, &found);
		Assert(found);
	}
}