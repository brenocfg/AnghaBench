#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int nb_regions; int /*<<< orphan*/ * length; int /*<<< orphan*/ * address; } ;
struct TYPE_5__ {TYPE_2__* priv; } ;
typedef  TYPE_1__ HWMapDescriptor ;
typedef  TYPE_2__ DRMMapping ;
typedef  int /*<<< orphan*/  AVHWFramesContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_free (TYPE_2__*) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void drm_unmap_frame(AVHWFramesContext *hwfc,
                            HWMapDescriptor *hwmap)
{
    DRMMapping *map = hwmap->priv;
    int i;

    for (i = 0; i < map->nb_regions; i++)
        munmap(map->address[i], map->length[i]);

    av_free(map);
}