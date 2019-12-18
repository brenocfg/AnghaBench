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
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;
typedef  int /*<<< orphan*/  DistTableCacheEntry ;

/* Variables and functions */
 int /*<<< orphan*/  CreateDistTableCache () ; 
 int /*<<< orphan*/  DistTableCacheHash ; 
 int /*<<< orphan*/  ResetDistTableCacheEntry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ hash_seq_search (int /*<<< orphan*/ *) ; 

void
FlushDistTableCache(void)
{
	DistTableCacheEntry *cacheEntry = NULL;
	HASH_SEQ_STATUS status;

	hash_seq_init(&status, DistTableCacheHash);

	while ((cacheEntry = (DistTableCacheEntry *) hash_seq_search(&status)) != NULL)
	{
		ResetDistTableCacheEntry(cacheEntry);
	}

	hash_destroy(DistTableCacheHash);
	CreateDistTableCache();
}