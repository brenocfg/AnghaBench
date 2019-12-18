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
typedef  scalar_t__ u64 ;
struct seq_file {int dummy; } ;
struct cgroup_map_cb {struct seq_file* state; } ;

/* Variables and functions */
 int seq_printf (struct seq_file*,char*,char const*,unsigned long long) ; 

__attribute__((used)) static int cgroup_map_add(struct cgroup_map_cb *cb, const char *key, u64 value)
{
	struct seq_file *sf = cb->state;
	return seq_printf(sf, "%s %llu\n", key, (unsigned long long)value);
}