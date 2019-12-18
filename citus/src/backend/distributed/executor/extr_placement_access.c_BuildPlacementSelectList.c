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
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/ * BuildPlacementAccessList (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLACEMENT_ACCESS_SELECT ; 

__attribute__((used)) static List *
BuildPlacementSelectList(int32 groupId, List *relationShardList)
{
	return BuildPlacementAccessList(groupId, relationShardList, PLACEMENT_ACCESS_SELECT);
}