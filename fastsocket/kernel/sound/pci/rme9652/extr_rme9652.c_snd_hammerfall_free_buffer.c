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
struct TYPE_2__ {int /*<<< orphan*/ * dev; } ;
struct snd_dma_buffer {TYPE_1__ dev; scalar_t__ area; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_dma_pci_buf_id (struct pci_dev*) ; 
 int /*<<< orphan*/  snd_dma_reserve_buf (struct snd_dma_buffer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_hammerfall_free_buffer(struct snd_dma_buffer *dmab, struct pci_dev *pci)
{
	if (dmab->area) {
		dmab->dev.dev = NULL; /* make it anonymous */
		snd_dma_reserve_buf(dmab, snd_dma_pci_buf_id(pci));
	}
}