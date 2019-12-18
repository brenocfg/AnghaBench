#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int numareas; TYPE_1__* areasettings; int /*<<< orphan*/  loaded; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*) ;} ;
struct TYPE_4__ {int presencetype; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRT_ERROR ; 
 TYPE_3__ aasworld ; 
 TYPE_2__ botimport ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 

int AAS_AreaPresenceType(int areanum)
{
	if (!aasworld.loaded) return 0;
	if (areanum <= 0 || areanum >= aasworld.numareas)
	{
		botimport.Print(PRT_ERROR, "AAS_AreaPresenceType: invalid area number\n");
		return 0;
	} //end if
	return aasworld.areasettings[areanum].presencetype;
}