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
struct etr_aib {int dummy; } ;
struct clock_sync_data {int etr_port; int /*<<< orphan*/  cpus; struct etr_aib* etr_aib; } ;
typedef  int /*<<< orphan*/  etr_sync ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  cpu_online_map ; 
 int etr_aib_follows (struct etr_aib*,struct etr_aib*,int) ; 
 struct etr_aib etr_port0 ; 
 struct etr_aib etr_port1 ; 
 int /*<<< orphan*/  etr_sync_clock ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 int /*<<< orphan*/  memcpy (struct etr_aib*,struct etr_aib*,int) ; 
 int /*<<< orphan*/  memset (struct clock_sync_data*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ num_online_cpus () ; 
 int /*<<< orphan*/  put_online_cpus () ; 
 int stop_machine (int /*<<< orphan*/ ,struct clock_sync_data*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int etr_sync_clock_stop(struct etr_aib *aib, int port)
{
	struct clock_sync_data etr_sync;
	struct etr_aib *sync_port;
	int follows;
	int rc;

	/* Check if the current aib is adjacent to the sync port aib. */
	sync_port = (port == 0) ? &etr_port0 : &etr_port1;
	follows = etr_aib_follows(sync_port, aib, port);
	memcpy(sync_port, aib, sizeof(*aib));
	if (!follows)
		return -EAGAIN;
	memset(&etr_sync, 0, sizeof(etr_sync));
	etr_sync.etr_aib = aib;
	etr_sync.etr_port = port;
	get_online_cpus();
	atomic_set(&etr_sync.cpus, num_online_cpus() - 1);
	rc = stop_machine(etr_sync_clock, &etr_sync, &cpu_online_map);
	put_online_cpus();
	return rc;
}