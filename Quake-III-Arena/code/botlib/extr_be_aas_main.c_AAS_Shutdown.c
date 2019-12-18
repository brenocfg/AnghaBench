#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  aas_t ;
struct TYPE_5__ {int /*<<< orphan*/  initialized; scalar_t__ entities; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_DumpAASData () ; 
 int /*<<< orphan*/  AAS_DumpBSPData () ; 
 int /*<<< orphan*/  AAS_FreeAASLinkHeap () ; 
 int /*<<< orphan*/  AAS_FreeAASLinkedEntities () ; 
 int /*<<< orphan*/  AAS_FreeRoutingCaches () ; 
 int /*<<< orphan*/  AAS_ShutdownAlternativeRouting () ; 
 int /*<<< orphan*/  Com_Memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FreeMemory (scalar_t__) ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 TYPE_2__ aasworld ; 
 TYPE_1__ botimport ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 

void AAS_Shutdown(void)
{
	AAS_ShutdownAlternativeRouting();
	//
	AAS_DumpBSPData();
	//free routing caches
	AAS_FreeRoutingCaches();
	//free aas link heap
	AAS_FreeAASLinkHeap();
	//free aas linked entities
	AAS_FreeAASLinkedEntities();
	//free the aas data
	AAS_DumpAASData();
	//free the entities
	if (aasworld.entities) FreeMemory(aasworld.entities);
	//clear the aasworld structure
	Com_Memset(&aasworld, 0, sizeof(aas_t));
	//aas has not been initialized
	aasworld.initialized = qfalse;
	//NOTE: as soon as a new .bsp file is loaded the .bsp file memory is
	// freed an reallocated, so there's no need to free that memory here
	//print shutdown
	botimport.Print(PRT_MESSAGE, "AAS shutdown.\n");
}