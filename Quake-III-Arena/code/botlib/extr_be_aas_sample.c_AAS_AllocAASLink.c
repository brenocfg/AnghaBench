#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * prev_ent; struct TYPE_5__* next_ent; } ;
typedef  TYPE_1__ aas_link_t ;
struct TYPE_7__ {TYPE_1__* freelinks; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PRT_FATAL ; 
 TYPE_3__ aasworld ; 
 scalar_t__ bot_developer ; 
 TYPE_2__ botimport ; 
 int /*<<< orphan*/  numaaslinks ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 

aas_link_t *AAS_AllocAASLink(void)
{
	aas_link_t *link;

	link = aasworld.freelinks;
	if (!link)
	{
#ifndef BSPC
		if (bot_developer)
#endif
		{
			botimport.Print(PRT_FATAL, "empty aas link heap\n");
		} //end if
		return NULL;
	} //end if
	if (aasworld.freelinks) aasworld.freelinks = aasworld.freelinks->next_ent;
	if (aasworld.freelinks) aasworld.freelinks->prev_ent = NULL;
	numaaslinks--;
	return link;
}