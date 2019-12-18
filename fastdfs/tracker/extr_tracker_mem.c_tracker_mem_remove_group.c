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
struct TYPE_2__ {int count; } ;
typedef  int /*<<< orphan*/  FDFSGroupInfo ;

/* Variables and functions */
 int ENOENT ; 
 TYPE_1__ g_groups ; 

__attribute__((used)) static int tracker_mem_remove_group(FDFSGroupInfo **groups, FDFSGroupInfo *pGroup)
{
	FDFSGroupInfo **ppGroup;
	FDFSGroupInfo **ppEnd;
	FDFSGroupInfo **pp;

    ppEnd = groups + g_groups.count;
    for (ppGroup=groups; ppGroup<ppEnd; ppGroup++)
    {
        if (*ppGroup == pGroup)
        {
            break;
        }
    }

    if (ppGroup == ppEnd)
    {
        return ENOENT;
    }

    for (pp=ppGroup + 1; pp<ppEnd; pp++)
    {
        *(pp - 1) = *pp;
    }

    return 0;
}