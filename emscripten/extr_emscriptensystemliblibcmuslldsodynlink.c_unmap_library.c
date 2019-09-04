#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dso {void* map; scalar_t__ map_len; TYPE_2__* loadmap; } ;
struct TYPE_4__ {size_t nsegs; TYPE_1__* segs; } ;
struct TYPE_3__ {scalar_t__ p_memsz; scalar_t__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  munmap (void*,scalar_t__) ; 

__attribute__((used)) static void unmap_library(struct dso *dso)
{
	if (dso->loadmap) {
		size_t i;
		for (i=0; i<dso->loadmap->nsegs; i++) {
			if (!dso->loadmap->segs[i].p_memsz)
				continue;
			munmap((void *)dso->loadmap->segs[i].addr,
				dso->loadmap->segs[i].p_memsz);
		}
		free(dso->loadmap);
	} else if (dso->map && dso->map_len) {
		munmap(dso->map, dso->map_len);
	}
}