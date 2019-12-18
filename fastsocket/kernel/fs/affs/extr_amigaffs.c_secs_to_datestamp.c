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
typedef  int u32 ;
typedef  int time_t ;
struct affs_date {void* ticks; void* mins; void* days; } ;
struct TYPE_2__ {int tz_minuteswest; } ;

/* Variables and functions */
 void* cpu_to_be32 (int) ; 
 TYPE_1__ sys_tz ; 

void
secs_to_datestamp(time_t secs, struct affs_date *ds)
{
	u32	 days;
	u32	 minute;

	secs -= sys_tz.tz_minuteswest * 60 + ((8 * 365 + 2) * 24 * 60 * 60);
	if (secs < 0)
		secs = 0;
	days    = secs / 86400;
	secs   -= days * 86400;
	minute  = secs / 60;
	secs   -= minute * 60;

	ds->days = cpu_to_be32(days);
	ds->mins = cpu_to_be32(minute);
	ds->ticks = cpu_to_be32(secs * 50);
}