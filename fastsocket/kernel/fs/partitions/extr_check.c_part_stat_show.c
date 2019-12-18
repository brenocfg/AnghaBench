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
struct hd_struct {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 size_t READ ; 
 size_t WRITE ; 
 struct hd_struct* dev_to_part (struct device*) ; 
 int /*<<< orphan*/  io_ticks ; 
 int /*<<< orphan*/ * ios ; 
 int /*<<< orphan*/  jiffies_to_msecs (int) ; 
 int /*<<< orphan*/ * merges ; 
 int /*<<< orphan*/  part_in_flight (struct hd_struct*) ; 
 int /*<<< orphan*/  part_round_stats (int,struct hd_struct*) ; 
 int part_stat_lock () ; 
 int part_stat_read (struct hd_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  part_stat_unlock () ; 
 int /*<<< orphan*/ * sectors ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,unsigned long long,int /*<<< orphan*/ ,int,int,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ticks ; 
 int /*<<< orphan*/  time_in_queue ; 

ssize_t part_stat_show(struct device *dev,
		       struct device_attribute *attr, char *buf)
{
	struct hd_struct *p = dev_to_part(dev);
	int cpu;

	cpu = part_stat_lock();
	part_round_stats(cpu, p);
	part_stat_unlock();
	return sprintf(buf,
		"%8lu %8lu %8llu %8u "
		"%8lu %8lu %8llu %8u "
		"%8u %8u %8u"
		"\n",
		part_stat_read(p, ios[READ]),
		part_stat_read(p, merges[READ]),
		(unsigned long long)part_stat_read(p, sectors[READ]),
		jiffies_to_msecs(part_stat_read(p, ticks[READ])),
		part_stat_read(p, ios[WRITE]),
		part_stat_read(p, merges[WRITE]),
		(unsigned long long)part_stat_read(p, sectors[WRITE]),
		jiffies_to_msecs(part_stat_read(p, ticks[WRITE])),
		part_in_flight(p),
		jiffies_to_msecs(part_stat_read(p, io_ticks)),
		jiffies_to_msecs(part_stat_read(p, time_in_queue)));
}