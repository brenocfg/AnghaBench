#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ipw2100_priv {TYPE_3__* tx_buffers; int /*<<< orphan*/  pci_dev; int /*<<< orphan*/  tx_queue; } ;
struct ipw2100_data_header {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  data_phys; scalar_t__ data; int /*<<< orphan*/ * txb; } ;
struct TYPE_5__ {TYPE_1__ d_struct; } ;
struct TYPE_6__ {TYPE_2__ info; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_DEBUG_INFO (char*) ; 
 int TX_PENDED_QUEUE_LENGTH ; 
 int /*<<< orphan*/  bd_queue_free (struct ipw2100_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 int /*<<< orphan*/  libipw_txb_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipw2100_tx_free(struct ipw2100_priv *priv)
{
	int i;

	IPW_DEBUG_INFO("enter\n");

	bd_queue_free(priv, &priv->tx_queue);

	if (!priv->tx_buffers)
		return;

	for (i = 0; i < TX_PENDED_QUEUE_LENGTH; i++) {
		if (priv->tx_buffers[i].info.d_struct.txb) {
			libipw_txb_free(priv->tx_buffers[i].info.d_struct.
					   txb);
			priv->tx_buffers[i].info.d_struct.txb = NULL;
		}
		if (priv->tx_buffers[i].info.d_struct.data)
			pci_free_consistent(priv->pci_dev,
					    sizeof(struct ipw2100_data_header),
					    priv->tx_buffers[i].info.d_struct.
					    data,
					    priv->tx_buffers[i].info.d_struct.
					    data_phys);
	}

	kfree(priv->tx_buffers);
	priv->tx_buffers = NULL;

	IPW_DEBUG_INFO("exit\n");
}