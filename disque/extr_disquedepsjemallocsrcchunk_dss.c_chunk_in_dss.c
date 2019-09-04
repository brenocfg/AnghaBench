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
 scalar_t__ dss_base ; 
 scalar_t__ dss_max ; 
 int /*<<< orphan*/  dss_mtx ; 
 int /*<<< orphan*/  have_dss ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *) ; 

bool
chunk_in_dss(void *chunk)
{
	bool ret;

	cassert(have_dss);

	malloc_mutex_lock(&dss_mtx);
	if ((uintptr_t)chunk >= (uintptr_t)dss_base
	    && (uintptr_t)chunk < (uintptr_t)dss_max)
		ret = true;
	else
		ret = false;
	malloc_mutex_unlock(&dss_mtx);

	return (ret);
}