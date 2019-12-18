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
struct TYPE_4__ {int numareas; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,int) ;} ;

/* Variables and functions */
 scalar_t__ AAS_CheckAreaForPossiblePortals (int) ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 TYPE_2__ aasworld ; 
 TYPE_1__ botimport ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int) ; 

void AAS_FindPossiblePortals(void)
{
	int i, numpossibleportals;

	numpossibleportals = 0;
	for (i = 1; i < aasworld.numareas; i++)
	{
		numpossibleportals += AAS_CheckAreaForPossiblePortals(i);
	} //end for
	botimport.Print(PRT_MESSAGE, "\r%6d possible portal areas\n", numpossibleportals);
}