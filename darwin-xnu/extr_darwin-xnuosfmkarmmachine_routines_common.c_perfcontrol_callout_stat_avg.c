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
typedef  int uint64_t ;
typedef  size_t perfcontrol_callout_type_t ;
typedef  size_t perfcontrol_callout_stat_t ;

/* Variables and functions */
 int* perfcontrol_callout_count ; 
 int** perfcontrol_callout_stats ; 
 int /*<<< orphan*/  perfcontrol_callout_stats_enabled ; 

uint64_t perfcontrol_callout_stat_avg(perfcontrol_callout_type_t type,
	perfcontrol_callout_stat_t stat)
{
    if (!perfcontrol_callout_stats_enabled)
        return 0;
    return (perfcontrol_callout_stats[type][stat] / perfcontrol_callout_count[type]);
}