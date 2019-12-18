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
struct node_entry {int generation; scalar_t__ needs_probe; int /*<<< orphan*/  device; scalar_t__ in_limbo; struct hpsb_host* host; } ;
struct hpsb_host {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct device* get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nodemgr_irm_write_bc (struct node_entry*,int) ; 
 int /*<<< orphan*/  nodemgr_pause_ne (struct node_entry*) ; 
 int /*<<< orphan*/  nodemgr_process_root_directory (struct node_entry*) ; 
 int /*<<< orphan*/  nodemgr_update_pdrv (struct node_entry*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 

__attribute__((used)) static void nodemgr_probe_ne(struct hpsb_host *host, struct node_entry *ne,
			     int generation)
{
	struct device *dev;

	if (ne->host != host || ne->in_limbo)
		return;

	dev = get_device(&ne->device);
	if (!dev)
		return;

	nodemgr_irm_write_bc(ne, generation);

	/* If "needs_probe", then this is either a new or changed node we
	 * rescan totally. If the generation matches for an existing node
	 * (one that existed prior to the bus reset) we send update calls
	 * down to the drivers. Otherwise, this is a dead node and we
	 * suspend it. */
	if (ne->needs_probe)
		nodemgr_process_root_directory(ne);
	else if (ne->generation == generation)
		nodemgr_update_pdrv(ne);
	else
		nodemgr_pause_ne(ne);

	put_device(dev);
}