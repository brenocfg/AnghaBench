#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  union s_fp_descr {int dummy; } s_fp_descr ;
typedef  int u_long ;
struct s_smt_tx_queue {int tx_free; scalar_t__ tx_used; struct s_smt_fp_txd volatile* tx_curr_get; } ;
typedef  struct s_smt_fp_txd {struct s_smt_fp_txd volatile* txd_next; int /*<<< orphan*/  txd_tbctrl; } volatile s_smt_fp_txd ;
struct TYPE_3__ {struct s_smt_tx_queue** tx; } ;
struct TYPE_4__ {TYPE_1__ fp; } ;
struct s_smc {TYPE_2__ hw; } ;
typedef  int /*<<< orphan*/  SMbuf ;

/* Variables and functions */
 int BMU_EOF ; 
 int BMU_OWN ; 
 int BMU_SMT_TX ; 
 int /*<<< orphan*/  CR_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DB_TX (char*,...) ; 
 int /*<<< orphan*/  DDI_DMA_SYNC_FORCPU ; 
 int DMA_RD ; 
 int /*<<< orphan*/  DRV_BUF_FLUSH (struct s_smt_fp_txd volatile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDD_TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int QUEUE_A0 ; 
 int QUEUE_S ; 
 int /*<<< orphan*/  dma_complete (struct s_smc*,union s_fp_descr volatile*,int) ; 
 int /*<<< orphan*/ * get_txd_mb (struct s_smc*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_drv_tx_complete (struct s_smc*,struct s_smt_fp_txd volatile*) ; 
 int /*<<< orphan*/  smt_free_mbuf (struct s_smc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mac_drv_clear_txd(struct s_smc *smc)
{
	struct s_smt_tx_queue *queue ;
	struct s_smt_fp_txd volatile *t1 ;
	struct s_smt_fp_txd volatile *t2 = NULL ;
	SMbuf *mb ;
	u_long	tbctrl ;
	int i ;
	int frag_count ;
	int n ;

	NDD_TRACE("THcB",0,0,0) ;
	for (i = QUEUE_S; i <= QUEUE_A0; i++) {
		queue = smc->hw.fp.tx[i] ;
		t1 = queue->tx_curr_get ;
		DB_TX("clear_txd: QUEUE = %d (0=sync/1=async)",i,0,5) ;

		for ( ; ; ) {
			frag_count = 0 ;

			do {
				DRV_BUF_FLUSH(t1,DDI_DMA_SYNC_FORCPU) ;
				DB_TX("check OWN/EOF bit of TxD 0x%x",t1,0,5) ;
				tbctrl = le32_to_cpu(CR_READ(t1->txd_tbctrl));

				if (tbctrl & BMU_OWN || !queue->tx_used){
					DB_TX("End of TxDs queue %d",i,0,4) ;
					goto free_next_queue ;	/* next queue */
				}
				t1 = t1->txd_next ;
				frag_count++ ;
			} while (!(tbctrl & BMU_EOF)) ;

			t1 = queue->tx_curr_get ;
			for (n = frag_count; n; n--) {
				tbctrl = le32_to_cpu(t1->txd_tbctrl) ;
				dma_complete(smc,
					(union s_fp_descr volatile *) t1,
					(int) (DMA_RD |
					((tbctrl & BMU_SMT_TX) >> 18))) ;
				t2 = t1 ;
				t1 = t1->txd_next ;
			}

			if (tbctrl & BMU_SMT_TX) {
				mb = get_txd_mb(smc) ;
				smt_free_mbuf(smc,mb) ;
			}
			else {
#ifndef PASS_1ST_TXD_2_TX_COMP
				DB_TX("mac_drv_tx_comp for TxD 0x%x",t2,0,4) ;
				mac_drv_tx_complete(smc,t2) ;
#else
				DB_TX("mac_drv_tx_comp for TxD 0x%x",
					queue->tx_curr_get,0,4) ;
				mac_drv_tx_complete(smc,queue->tx_curr_get) ;
#endif
			}
			queue->tx_curr_get = t1 ;
			queue->tx_free += frag_count ;
			queue->tx_used -= frag_count ;
		}
free_next_queue: ;
	}
	NDD_TRACE("THcE",0,0,0) ;
}