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
struct TYPE_2__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PRT_MESSAGE ; 
 TYPE_1__ botimport ; 
 int /*<<< orphan*/  numareacacheupdates ; 
 int /*<<< orphan*/  numportalcacheupdates ; 
 int /*<<< orphan*/  routingcachesize ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void AAS_RoutingInfo(void)
{
	botimport.Print(PRT_MESSAGE, "%d area cache updates\n", numareacacheupdates);
	botimport.Print(PRT_MESSAGE, "%d portal cache updates\n", numportalcacheupdates);
	botimport.Print(PRT_MESSAGE, "%d bytes routing cache\n", routingcachesize);
}