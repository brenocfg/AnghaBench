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
struct device {int dummy; } ;
struct ata_port {int port_no; } ;
struct ata_host {int n_ports; struct ata_port** ports; struct device* dev; int /*<<< orphan*/  eh_mutex; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ata_host_release ; 
 struct ata_port* ata_port_alloc (struct ata_host*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct ata_host*) ; 
 int /*<<< orphan*/  devres_add (struct device*,struct ata_host*) ; 
 struct ata_host* devres_alloc (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_open_group (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_release_group (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devres_remove_group (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct ata_host *ata_host_alloc(struct device *dev, int max_ports)
{
	struct ata_host *host;
	size_t sz;
	int i;

	DPRINTK("ENTER\n");

	if (!devres_open_group(dev, NULL, GFP_KERNEL))
		return NULL;

	/* alloc a container for our list of ATA ports (buses) */
	sz = sizeof(struct ata_host) + (max_ports + 1) * sizeof(void *);
	/* alloc a container for our list of ATA ports (buses) */
	host = devres_alloc(ata_host_release, sz, GFP_KERNEL);
	if (!host)
		goto err_out;

	devres_add(dev, host);
	dev_set_drvdata(dev, host);

	spin_lock_init(&host->lock);
	mutex_init(&host->eh_mutex);
	host->dev = dev;
	host->n_ports = max_ports;

	/* allocate ports bound to this host */
	for (i = 0; i < max_ports; i++) {
		struct ata_port *ap;

		ap = ata_port_alloc(host);
		if (!ap)
			goto err_out;

		ap->port_no = i;
		host->ports[i] = ap;
	}

	devres_remove_group(dev, NULL);
	return host;

 err_out:
	devres_release_group(dev, NULL);
	return NULL;
}