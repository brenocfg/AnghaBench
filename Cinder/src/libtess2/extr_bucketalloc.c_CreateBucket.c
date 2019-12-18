#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct BucketAlloc {int itemSize; int bucketSize; void* freelist; TYPE_2__* buckets; TYPE_1__* alloc; } ;
struct TYPE_4__ {struct TYPE_4__* next; } ;
struct TYPE_3__ {int /*<<< orphan*/  userData; scalar_t__ (* memalloc ) (int /*<<< orphan*/ ,size_t) ;} ;
typedef  TYPE_2__ Bucket ;

/* Variables and functions */
 scalar_t__ stub1 (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int CreateBucket( struct BucketAlloc* ba )
{
	size_t size;
	Bucket* bucket;
	void* freelist;
	unsigned char* head;
	unsigned char* it;

	// Allocate memory for the bucket
	size = sizeof(Bucket) + ba->itemSize * ba->bucketSize;
	bucket = (Bucket*)ba->alloc->memalloc( ba->alloc->userData, size );
	if ( !bucket )
		return 0;
	bucket->next = 0;

	// Add the bucket into the list of buckets.
	bucket->next = ba->buckets;
	ba->buckets = bucket;

	// Add new items to the free list.
	freelist = ba->freelist;
	head = (unsigned char*)bucket + sizeof(Bucket);
	it = head + ba->itemSize * ba->bucketSize;
	do
	{
		it -= ba->itemSize;
		// Store pointer to next free item.
		*((void**)it) = freelist;
		// Pointer to next location containing a free item.
		freelist = (void*)it;
	}
	while ( it != head );
	// Update pointer to next location containing a free item.
	ba->freelist = (void*)it;

	return 1;
}