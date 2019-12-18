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
struct TYPE_2__ {int /*<<< orphan*/  threads_timedout; int /*<<< orphan*/  threads_woken; int /*<<< orphan*/  sockets_queued; int /*<<< orphan*/  packets; } ;
struct svc_pool {TYPE_1__ sp_stats; int /*<<< orphan*/  sp_id; } ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 void* SEQ_START_TOKEN ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int svc_pool_stats_show(struct seq_file *m, void *p)
{
	struct svc_pool *pool = p;

	if (p == SEQ_START_TOKEN) {
		seq_puts(m, "# pool packets-arrived sockets-enqueued threads-woken threads-timedout\n");
		return 0;
	}

	seq_printf(m, "%u %lu %lu %lu %lu\n",
		pool->sp_id,
		pool->sp_stats.packets,
		pool->sp_stats.sockets_queued,
		pool->sp_stats.threads_woken,
		pool->sp_stats.threads_timedout);

	return 0;
}