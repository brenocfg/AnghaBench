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
 int /*<<< orphan*/  dss_mtx ; 
 scalar_t__ have_dss ; 
 int /*<<< orphan*/  malloc_mutex_prefork (int /*<<< orphan*/ *) ; 

void
chunk_dss_prefork(void)
{

	if (have_dss)
		malloc_mutex_prefork(&dss_mtx);
}