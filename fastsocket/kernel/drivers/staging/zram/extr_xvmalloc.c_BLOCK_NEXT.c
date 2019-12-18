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
struct block_header {int size; } ;

/* Variables and functions */
 int XV_ALIGN ; 

__attribute__((used)) static struct block_header *BLOCK_NEXT(struct block_header *block)
{
	return (struct block_header *)
		((char *)block + block->size + XV_ALIGN);
}