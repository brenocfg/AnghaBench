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
 int B_FALSE ; 
 int B_TRUE ; 
 size_t UINT64_MAX ; 
 size_t dtrace_buffer_memory_inuse ; 
 size_t dtrace_buffer_memory_maxsize ; 

__attribute__((used)) static int
dtrace_buffer_canalloc(size_t size)
{
	if (size > (UINT64_MAX - dtrace_buffer_memory_inuse))
		return (B_FALSE);
	if ((size + dtrace_buffer_memory_inuse) > dtrace_buffer_memory_maxsize)
		return (B_FALSE);

	return (B_TRUE);
}