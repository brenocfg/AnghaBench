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
struct TYPE_4__ {int queues; int removes; int fins; int reads; int writes; int miscs; int disconnects; int aborts; int bus_resets; int host_resets; } ;
struct TYPE_5__ {TYPE_1__ stats; } ;
typedef  TYPE_2__ FAS216_Info ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,int,int,int,int,int,int,int) ; 

int fas216_print_stats(FAS216_Info *info, char *buffer)
{
	char *p = buffer;

	p += sprintf(p, "\n"
			"Command Statistics:\n"
			" Queued     : %u\n"
			" Issued     : %u\n"
			" Completed  : %u\n"
			" Reads      : %u\n"
			" Writes     : %u\n"
			" Others     : %u\n"
			" Disconnects: %u\n"
			" Aborts     : %u\n"
			" Bus resets : %u\n"
			" Host resets: %u\n",
			info->stats.queues,	 info->stats.removes,
			info->stats.fins,	 info->stats.reads,
			info->stats.writes,	 info->stats.miscs,
			info->stats.disconnects, info->stats.aborts,
			info->stats.bus_resets,	 info->stats.host_resets);

	return p - buffer;
}