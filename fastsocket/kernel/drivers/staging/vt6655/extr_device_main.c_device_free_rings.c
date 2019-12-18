#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nRxDescs0; int nRxDescs1; int* nTxDescs; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_bufs_dma0; scalar_t__ tx0_bufs; TYPE_1__ sOpts; int /*<<< orphan*/  pcid; int /*<<< orphan*/  pool_dma; scalar_t__ aRD0Ring; } ;
typedef  int /*<<< orphan*/  STxDesc ;
typedef  int /*<<< orphan*/  SRxDesc ;
typedef  TYPE_2__* PSDevice ;

/* Variables and functions */
 int CB_BEACON_BUF_SIZE ; 
 int CB_MAX_BUF_SIZE ; 
 int PKT_BUF_SZ ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void device_free_rings(PSDevice pDevice) {

    pci_free_consistent(pDevice->pcid,
            pDevice->sOpts.nRxDescs0 * sizeof(SRxDesc) +
            pDevice->sOpts.nRxDescs1 * sizeof(SRxDesc) +
            pDevice->sOpts.nTxDescs[0] * sizeof(STxDesc) +
            pDevice->sOpts.nTxDescs[1] * sizeof(STxDesc)
            ,
            pDevice->aRD0Ring, pDevice->pool_dma
        );

    if (pDevice->tx0_bufs)
        pci_free_consistent(pDevice->pcid,
           pDevice->sOpts.nTxDescs[0] * PKT_BUF_SZ +
           pDevice->sOpts.nTxDescs[1] * PKT_BUF_SZ +
           CB_BEACON_BUF_SIZE +
           CB_MAX_BUF_SIZE,
           pDevice->tx0_bufs, pDevice->tx_bufs_dma0
        );
}