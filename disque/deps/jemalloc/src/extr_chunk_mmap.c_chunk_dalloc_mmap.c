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

/* Variables and functions */
 scalar_t__ config_munmap ; 
 int /*<<< orphan*/  pages_unmap (void*,size_t) ; 

bool
chunk_dalloc_mmap(void *chunk, size_t size)
{

	if (config_munmap)
		pages_unmap(chunk, size);

	return (!config_munmap);
}