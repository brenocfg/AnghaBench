#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct TYPE_3__** top; struct TYPE_3__** dir; } ;

/* Variables and functions */
 int EHEA_MAP_ENTRIES ; 
 TYPE_1__* ehea_bmap ; 
 int /*<<< orphan*/  ehea_busmap_mutex ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void ehea_destroy_busmap(void)
{
	int top, dir;
	mutex_lock(&ehea_busmap_mutex);
	if (!ehea_bmap)
		goto out_destroy;

	for (top = 0; top < EHEA_MAP_ENTRIES; top++) {
		if (!ehea_bmap->top[top])
			continue;

		for (dir = 0; dir < EHEA_MAP_ENTRIES; dir++) {
			if (!ehea_bmap->top[top]->dir[dir])
				continue;

			kfree(ehea_bmap->top[top]->dir[dir]);
		}

		kfree(ehea_bmap->top[top]);
	}

	kfree(ehea_bmap);
	ehea_bmap = NULL;
out_destroy:
	mutex_unlock(&ehea_busmap_mutex);
}