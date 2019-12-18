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
struct BucketAlloc {int itemSize; int bucketSize; void* freelist; int /*<<< orphan*/  name; TYPE_1__* buckets; } ;
struct TYPE_2__ {struct TYPE_2__* next; } ;
typedef  TYPE_1__ Bucket ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 

void bucketFree( struct BucketAlloc *ba, void *ptr )
{
#ifdef CHECK_BOUNDS
	int inBounds = 0;
	Bucket *bucket;

	// Check that the pointer is allocated with this allocator.
	bucket = ba->buckets;
	while ( bucket )
	{
		void *bucketMin = (void*)((unsigned char*)bucket + sizeof(Bucket));
		void *bucketMax = (void*)((unsigned char*)bucket + sizeof(Bucket) + ba->itemSize * ba->bucketSize);
		if ( ptr >= bucketMin && ptr < bucketMax )
		{
			inBounds = 1;
			break;
		}
		bucket = bucket->next;			
	}		

	if ( inBounds )
	{
		// Add the node in front of the free list.
		*(void**)ptr = ba->freelist;
		ba->freelist = ptr;
	}
	else
	{
		printf("ERROR! pointer 0x%p does not belong to allocator '%s'\n", ba->name);
	}
#else
	// Add the node in front of the free list.
	*(void**)ptr = ba->freelist;
	ba->freelist = ptr;
#endif
}