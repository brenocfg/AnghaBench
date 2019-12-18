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
struct BucketAlloc {struct BucketAlloc* buckets; scalar_t__ freelist; struct BucketAlloc* next; TYPE_1__* alloc; } ;
struct TYPE_2__ {int /*<<< orphan*/  userData; int /*<<< orphan*/  (* memfree ) (int /*<<< orphan*/ ,struct BucketAlloc*) ;} ;
typedef  TYPE_1__ TESSalloc ;
typedef  struct BucketAlloc Bucket ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct BucketAlloc*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct BucketAlloc*) ; 

void deleteBucketAlloc( struct BucketAlloc *ba )
{
	TESSalloc* alloc = ba->alloc;
	Bucket *bucket = ba->buckets;
	Bucket *next;
	while ( bucket )
	{
		next = bucket->next;
		alloc->memfree( alloc->userData, bucket );
		bucket = next;
	}		
	ba->freelist = 0;
	ba->buckets = 0;
	alloc->memfree( alloc->userData, ba );
}