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
typedef  int /*<<< orphan*/  wbstartstruct_t ;

/* Variables and functions */
 int /*<<< orphan*/  WI_initDeathmatchStats () ; 
 int /*<<< orphan*/  WI_initNetgameStats () ; 
 int /*<<< orphan*/  WI_initStats () ; 
 int /*<<< orphan*/  WI_initVariables (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WI_loadData () ; 
 scalar_t__ deathmatch ; 
 scalar_t__ netgame ; 

void WI_Start(wbstartstruct_t* wbstartstruct)
{

    WI_initVariables(wbstartstruct);
    WI_loadData();

    if (deathmatch)
	WI_initDeathmatchStats();
    else if (netgame)
	WI_initNetgameStats();
    else
	WI_initStats();
}