#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int isValid; } ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;
typedef  TYPE_1__ DistTableCacheEntry ;

/* Variables and functions */
 int /*<<< orphan*/  DistTableCacheHash ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ hash_seq_search (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
InvalidateDistTableCache(void)
{
	DistTableCacheEntry *cacheEntry = NULL;
	HASH_SEQ_STATUS status;

	hash_seq_init(&status, DistTableCacheHash);

	while ((cacheEntry = (DistTableCacheEntry *) hash_seq_search(&status)) != NULL)
	{
		cacheEntry->isValid = false;
	}
}