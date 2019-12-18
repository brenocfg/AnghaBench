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
struct ctl_table {int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  gid_t ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned int read_seqbegin (int /*<<< orphan*/ *) ; 
 scalar_t__ read_seqretry (int /*<<< orphan*/ *,unsigned int) ; 
 TYPE_1__ sysctl_local_ports ; 

__attribute__((used)) static void inet_get_ping_group_range_table(struct ctl_table *table, gid_t *low, gid_t *high)
{
	gid_t *data = table->data;
	unsigned seq;
	do {
		seq = read_seqbegin(&sysctl_local_ports.lock);

		*low = data[0];
		*high = data[1];
	} while (read_seqretry(&sysctl_local_ports.lock, seq));
}