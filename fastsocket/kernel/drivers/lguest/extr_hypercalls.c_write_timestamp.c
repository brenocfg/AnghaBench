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
struct timespec {int dummy; } ;
struct lg_cpu {TYPE_2__* lg; } ;
struct TYPE_4__ {TYPE_1__* lguest_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  time; } ;

/* Variables and functions */
 scalar_t__ copy_to_user (int /*<<< orphan*/ *,struct timespec*,int) ; 
 int /*<<< orphan*/  kill_guest (struct lg_cpu*,char*) ; 
 int /*<<< orphan*/  ktime_get_real_ts (struct timespec*) ; 

void write_timestamp(struct lg_cpu *cpu)
{
	struct timespec now;
	ktime_get_real_ts(&now);
	if (copy_to_user(&cpu->lg->lguest_data->time,
			 &now, sizeof(struct timespec)))
		kill_guest(cpu, "Writing timestamp");
}