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
typedef  int /*<<< orphan*/  u32 ;
struct block_header {int /*<<< orphan*/  size; } ;
typedef  scalar_t__ obj ;

/* Variables and functions */
 scalar_t__ XV_ALIGN ; 

u32 xv_get_object_size(void *obj)
{
	struct block_header *blk;

	blk = (struct block_header *)((char *)(obj) - XV_ALIGN);
	return blk->size;
}