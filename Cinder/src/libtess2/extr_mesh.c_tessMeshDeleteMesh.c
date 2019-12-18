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
struct TYPE_7__ {int /*<<< orphan*/  userData; int /*<<< orphan*/  (* memfree ) (int /*<<< orphan*/ ,TYPE_1__*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  faceBucket; int /*<<< orphan*/  vertexBucket; int /*<<< orphan*/  edgeBucket; } ;
typedef  TYPE_1__ TESSmesh ;
typedef  TYPE_2__ TESSalloc ;

/* Variables and functions */
 int /*<<< orphan*/  deleteBucketAlloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*) ; 

void tessMeshDeleteMesh( TESSalloc* alloc, TESSmesh *mesh )
{
	deleteBucketAlloc(mesh->edgeBucket);
	deleteBucketAlloc(mesh->vertexBucket);
	deleteBucketAlloc(mesh->faceBucket);

	alloc->memfree( alloc->userData, mesh );
}