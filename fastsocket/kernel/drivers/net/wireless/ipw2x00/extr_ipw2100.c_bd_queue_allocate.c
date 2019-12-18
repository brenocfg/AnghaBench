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
struct ipw2100_priv {int /*<<< orphan*/  pci_dev; } ;
struct ipw2100_bd_queue {int entries; int size; struct ipw2100_bd_queue* drv; int /*<<< orphan*/  nic; } ;
struct ipw2100_bd {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IPW_DEBUG_INFO (char*) ; 
 int /*<<< orphan*/  memset (struct ipw2100_bd_queue*,int /*<<< orphan*/ ,int) ; 
 struct ipw2100_bd_queue* pci_alloc_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bd_queue_allocate(struct ipw2100_priv *priv,
			     struct ipw2100_bd_queue *q, int entries)
{
	IPW_DEBUG_INFO("enter\n");

	memset(q, 0, sizeof(struct ipw2100_bd_queue));

	q->entries = entries;
	q->size = entries * sizeof(struct ipw2100_bd);
	q->drv = pci_alloc_consistent(priv->pci_dev, q->size, &q->nic);
	if (!q->drv) {
		IPW_DEBUG_INFO
		    ("can't allocate shared memory for buffer descriptors\n");
		return -ENOMEM;
	}
	memset(q->drv, 0, q->size);

	IPW_DEBUG_INFO("exit\n");

	return 0;
}