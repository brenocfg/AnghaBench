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
 int chunk_dalloc_mmap (void*,size_t) ; 
 int /*<<< orphan*/  chunk_in_dss (void*) ; 
 int /*<<< orphan*/  have_dss ; 

__attribute__((used)) static bool
chunk_dalloc_default(void *chunk, size_t size, bool committed,
    unsigned arena_ind)
{

	if (!have_dss || !chunk_in_dss(chunk))
		return (chunk_dalloc_mmap(chunk, size));
	return (true);
}