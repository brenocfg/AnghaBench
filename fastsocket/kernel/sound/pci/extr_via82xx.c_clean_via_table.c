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
struct TYPE_2__ {int /*<<< orphan*/ * area; } ;
struct viadev {int /*<<< orphan*/ * idx_table; TYPE_1__ table; } ;
struct snd_pcm_substream {int dummy; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_dma_free_pages (TYPE_1__*) ; 

__attribute__((used)) static int clean_via_table(struct viadev *dev, struct snd_pcm_substream *substream,
			   struct pci_dev *pci)
{
	if (dev->table.area) {
		snd_dma_free_pages(&dev->table);
		dev->table.area = NULL;
	}
	kfree(dev->idx_table);
	dev->idx_table = NULL;
	return 0;
}