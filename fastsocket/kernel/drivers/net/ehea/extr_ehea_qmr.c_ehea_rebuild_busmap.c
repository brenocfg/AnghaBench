#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct ehea_top_bmap {struct ehea_top_bmap** dir; scalar_t__* ent; } ;
struct ehea_dir_bmap {struct ehea_dir_bmap** dir; scalar_t__* ent; } ;
struct TYPE_2__ {struct ehea_top_bmap** top; } ;

/* Variables and functions */
 scalar_t__ EHEA_BUSMAP_START ; 
 int EHEA_MAP_ENTRIES ; 
 scalar_t__ EHEA_SECTSIZE ; 
 TYPE_1__* ehea_bmap ; 
 int /*<<< orphan*/  kfree (struct ehea_top_bmap*) ; 

__attribute__((used)) static void ehea_rebuild_busmap(void)
{
	u64 vaddr = EHEA_BUSMAP_START;
	int top, dir, idx;

	for (top = 0; top < EHEA_MAP_ENTRIES; top++) {
		struct ehea_top_bmap *ehea_top;
		int valid_dir_entries = 0;

		if (!ehea_bmap->top[top])
			continue;
		ehea_top = ehea_bmap->top[top];
		for (dir = 0; dir < EHEA_MAP_ENTRIES; dir++) {
			struct ehea_dir_bmap *ehea_dir;
			int valid_entries = 0;

			if (!ehea_top->dir[dir])
				continue;
			valid_dir_entries++;
			ehea_dir = ehea_top->dir[dir];
			for (idx = 0; idx < EHEA_MAP_ENTRIES; idx++) {
				if (!ehea_dir->ent[idx])
					continue;
				valid_entries++;
				ehea_dir->ent[idx] = vaddr;
				vaddr += EHEA_SECTSIZE;
			}
			if (!valid_entries) {
				ehea_top->dir[dir] = NULL;
				kfree(ehea_dir);
			}
		}
		if (!valid_dir_entries) {
			ehea_bmap->top[top] = NULL;
			kfree(ehea_top);
		}
	}
}