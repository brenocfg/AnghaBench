#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int time_used; char* id; int total_count; double success_count; } ;
typedef  TYPE_1__ EntryStat ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*,int,double,int,int,double,double) ; 

__attribute__((used)) static void print_stat_by(EntryStat *stats, const int entry_count)
{
	EntryStat *pEntry;
	EntryStat *pEnd;
	int seconds;

	pEnd = stats + entry_count;
	for (pEntry=stats; pEntry<pEnd; pEntry++)
	{
		seconds = pEntry->time_used / 1000;
		printf("%s %d %d %d %d %.2f %.2f\n", pEntry->id, pEntry->total_count, 
			pEntry->success_count, (int)(pEntry->time_used / 1000), 
			pEntry->total_count == 0 ? 0 : (int)(pEntry->time_used / pEntry->total_count), 
			seconds == 0 ? 0 : (double)pEntry->success_count / seconds, 
			pEntry->total_count > 0 ? 100.00 * pEntry->success_count / pEntry->total_count : 0.00);
	}
}