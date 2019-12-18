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
typedef  int /*<<< orphan*/  aas_link_t ;
struct TYPE_2__ {int numareas; int /*<<< orphan*/ ** arealinkedentities; int /*<<< orphan*/  loaded; } ;

/* Variables and functions */
 int /*<<< orphan*/  FreeMemory (int /*<<< orphan*/ **) ; 
 scalar_t__ GetClearedHunkMemory (int) ; 
 TYPE_1__ aasworld ; 

void AAS_InitAASLinkedEntities(void)
{
	if (!aasworld.loaded) return;
	if (aasworld.arealinkedentities) FreeMemory(aasworld.arealinkedentities);
	aasworld.arealinkedentities = (aas_link_t **) GetClearedHunkMemory(
						aasworld.numareas * sizeof(aas_link_t *));
}