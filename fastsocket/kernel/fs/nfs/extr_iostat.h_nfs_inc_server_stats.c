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
struct nfs_server {int /*<<< orphan*/  io_stats; } ;
struct nfs_iostats {int /*<<< orphan*/ * events; } ;
typedef  enum nfs_stat_eventcounters { ____Placeholder_nfs_stat_eventcounters } nfs_stat_eventcounters ;

/* Variables and functions */
 int get_cpu () ; 
 struct nfs_iostats* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_cpu () ; 

__attribute__((used)) static inline void nfs_inc_server_stats(const struct nfs_server *server,
					enum nfs_stat_eventcounters stat)
{
	struct nfs_iostats *iostats;
	int cpu;

	cpu = get_cpu();
	iostats = per_cpu_ptr(server->io_stats, cpu);
	iostats->events[stat]++;
	put_cpu();
}