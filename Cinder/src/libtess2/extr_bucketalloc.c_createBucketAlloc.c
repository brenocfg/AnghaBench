#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct BucketAlloc {char const* name; unsigned int itemSize; unsigned int bucketSize; scalar_t__ buckets; scalar_t__ freelist; TYPE_1__* alloc; } ;
struct TYPE_3__ {int /*<<< orphan*/  userData; int /*<<< orphan*/  (* memfree ) (int /*<<< orphan*/ ,struct BucketAlloc*) ;scalar_t__ (* memalloc ) (int /*<<< orphan*/ ,int) ;} ;
typedef  TYPE_1__ TESSalloc ;
typedef  struct BucketAlloc BucketAlloc ;

/* Variables and functions */
 int /*<<< orphan*/  CreateBucket (struct BucketAlloc*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct BucketAlloc*) ; 

struct BucketAlloc* createBucketAlloc( TESSalloc* alloc, const char* name,
									  unsigned int itemSize, unsigned int bucketSize )
{
	BucketAlloc* ba = (BucketAlloc*)alloc->memalloc( alloc->userData, sizeof(BucketAlloc) );

	ba->alloc = alloc;
	ba->name = name;
	ba->itemSize = itemSize;
	if ( ba->itemSize < sizeof(void*) )
		ba->itemSize = sizeof(void*);
	ba->bucketSize = bucketSize;
	ba->freelist = 0;
	ba->buckets = 0;

	if ( !CreateBucket( ba ) )
	{
		alloc->memfree( alloc->userData, ba );
		return 0;
	}

	return ba;
}