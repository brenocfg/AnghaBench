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
 int /*<<< orphan*/  cassert (int /*<<< orphan*/ ) ; 
 void* chunk_dss_sbrk (int /*<<< orphan*/ ) ; 
 void* dss_base ; 
 void* dss_max ; 
 int /*<<< orphan*/  dss_mtx ; 
 void* dss_prev ; 
 int /*<<< orphan*/  have_dss ; 
 scalar_t__ malloc_mutex_init (int /*<<< orphan*/ *) ; 

bool
chunk_dss_boot(void)
{

	cassert(have_dss);

	if (malloc_mutex_init(&dss_mtx))
		return (true);
	dss_base = chunk_dss_sbrk(0);
	dss_prev = dss_base;
	dss_max = dss_base;

	return (false);
}