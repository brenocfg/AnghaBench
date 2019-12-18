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
 int /*<<< orphan*/  OSAddAtomic (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cs_blob_generation_count ; 
 int /*<<< orphan*/  printf (char*) ; 

void
cs_blob_reset_cache()
{
	/* incrementing odd no by 2 makes sure '0' is never reached. */
	OSAddAtomic(+2, &cs_blob_generation_count);
	printf("Reseting cs_blob cache from all vnodes. \n");
}