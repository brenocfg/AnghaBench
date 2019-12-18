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
 int /*<<< orphan*/  EHEA_BUSMAP_ADD_SECT ; 
 int /*<<< orphan*/  ehea_busmap_mutex ; 
 int ehea_update_busmap (unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int ehea_add_sect_bmap(unsigned long pfn, unsigned long nr_pages)
{
	int ret;

	mutex_lock(&ehea_busmap_mutex);
	ret = ehea_update_busmap(pfn, nr_pages, EHEA_BUSMAP_ADD_SECT);
	mutex_unlock(&ehea_busmap_mutex);
	return ret;
}