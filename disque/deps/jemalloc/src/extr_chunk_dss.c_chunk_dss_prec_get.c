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
typedef  int /*<<< orphan*/  dss_prec_t ;

/* Variables and functions */
 int /*<<< orphan*/  dss_mtx ; 
 int /*<<< orphan*/  dss_prec_default ; 
 int /*<<< orphan*/  dss_prec_disabled ; 
 int /*<<< orphan*/  have_dss ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *) ; 

dss_prec_t
chunk_dss_prec_get(void)
{
	dss_prec_t ret;

	if (!have_dss)
		return (dss_prec_disabled);
	malloc_mutex_lock(&dss_mtx);
	ret = dss_prec_default;
	malloc_mutex_unlock(&dss_mtx);
	return (ret);
}