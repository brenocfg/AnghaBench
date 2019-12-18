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
struct scc_ports {struct ide_host* host; scalar_t__ dma; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct ide_port_info {int dummy; } ;
struct ide_hw {int /*<<< orphan*/ * dev; int /*<<< orphan*/  irq; scalar_t__* io_ports_array; } ;
struct ide_host {int dummy; } ;
typedef  int /*<<< orphan*/  hw ;

/* Variables and functions */
 int ide_host_add (struct ide_port_info const*,struct ide_hw**,int,struct ide_host**) ; 
 int /*<<< orphan*/  memset (struct ide_hw*,int /*<<< orphan*/ ,int) ; 
 struct scc_ports* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static int scc_ide_setup_pci_device(struct pci_dev *dev,
				    const struct ide_port_info *d)
{
	struct scc_ports *ports = pci_get_drvdata(dev);
	struct ide_host *host;
	struct ide_hw hw, *hws[] = { &hw };
	int i, rc;

	memset(&hw, 0, sizeof(hw));
	for (i = 0; i <= 8; i++)
		hw.io_ports_array[i] = ports->dma + 0x20 + i * 4;
	hw.irq = dev->irq;
	hw.dev = &dev->dev;

	rc = ide_host_add(d, hws, 1, &host);
	if (rc)
		return rc;

	ports->host = host;

	return 0;
}