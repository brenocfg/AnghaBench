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
struct BucketAlloc {void* freelist; } ;

/* Variables and functions */
 int /*<<< orphan*/  CreateBucket (struct BucketAlloc*) ; 
 void* NextFreeItem (struct BucketAlloc*) ; 

void* bucketAlloc( struct BucketAlloc *ba )
{
	void *it;

	// If running out of memory, allocate new bucket and update the freelist.
	if ( !ba->freelist || !NextFreeItem( ba ) )
	{
		if ( !CreateBucket( ba ) )
			return 0;
	}

	// Pop item from in front of the free list.
	it = ba->freelist;
	ba->freelist = NextFreeItem( ba );

	return it;
}