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
struct TYPE_3__ {int /*<<< orphan*/ * bam_cache; int /*<<< orphan*/ * XferInfo; int /*<<< orphan*/ * EUNInfo; int /*<<< orphan*/ * VirtualPageMap; int /*<<< orphan*/ * VirtualBlockMap; } ;
typedef  TYPE_1__ partition_t ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ftl_freepart(partition_t *part)
{
	vfree(part->VirtualBlockMap);
	part->VirtualBlockMap = NULL;
	kfree(part->VirtualPageMap);
	part->VirtualPageMap = NULL;
	kfree(part->EUNInfo);
	part->EUNInfo = NULL;
	kfree(part->XferInfo);
	part->XferInfo = NULL;
	kfree(part->bam_cache);
	part->bam_cache = NULL;
}