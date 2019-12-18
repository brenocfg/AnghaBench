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
 unsigned int NALLOCS_PER_THREAD ; 
 void* btalloc (int,unsigned int) ; 

__attribute__((used)) static void *
alloc_from_permuted_backtrace(unsigned thd_ind, unsigned iteration)
{

	return (btalloc(1, thd_ind*NALLOCS_PER_THREAD + iteration));
}