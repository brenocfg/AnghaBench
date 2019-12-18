#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  union s_fp_descr {int dummy; } s_fp_descr ;
typedef  int /*<<< orphan*/  u_long ;
struct s_smt_tx_queue {int tx_free; scalar_t__ tx_used; struct s_smt_fp_txd volatile* tx_curr_get; struct s_smt_fp_txd volatile* tx_curr_put; } ;
struct s_smt_fp_txd {int /*<<< orphan*/  txd_ntdadr; } ;
struct s_smt_fp_rxd {int dummy; } ;
struct TYPE_7__ {struct s_smt_tx_queue** tx; } ;
struct TYPE_8__ {TYPE_3__ fp; } ;
struct TYPE_5__ {scalar_t__ descr_p; } ;
struct TYPE_6__ {TYPE_1__ hwm; } ;
struct s_smc {TYPE_4__ hw; TYPE_2__ os; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B5_XA_DA ; 
 int /*<<< orphan*/  B5_XS_DA ; 
 int /*<<< orphan*/  DB_GEN (char*,int,int /*<<< orphan*/ ,int) ; 
 int HWM_ASYNC_TXD_COUNT ; 
 int HWM_SYNC_TXD_COUNT ; 
 size_t QUEUE_A0 ; 
 size_t QUEUE_S ; 
 int SMT_R1_RXD_COUNT ; 
 int /*<<< orphan*/  init_descr_ring (struct s_smc*,union s_fp_descr volatile*,int) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outpd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_txd_ring(struct s_smc *smc)
{
	struct s_smt_fp_txd volatile *ds ;
	struct s_smt_tx_queue *queue ;
	u_long	phys ;

	/*
	 * initialize the transmit descriptors
	 */
	ds = (struct s_smt_fp_txd volatile *) ((char *)smc->os.hwm.descr_p +
		SMT_R1_RXD_COUNT*sizeof(struct s_smt_fp_rxd)) ;
	queue = smc->hw.fp.tx[QUEUE_A0] ;
	DB_GEN("Init async TxD ring, %d TxDs ",HWM_ASYNC_TXD_COUNT,0,3) ;
	(void)init_descr_ring(smc,(union s_fp_descr volatile *)ds,
		HWM_ASYNC_TXD_COUNT) ;
	phys = le32_to_cpu(ds->txd_ntdadr) ;
	ds++ ;
	queue->tx_curr_put = queue->tx_curr_get = ds ;
	ds-- ;
	queue->tx_free = HWM_ASYNC_TXD_COUNT ;
	queue->tx_used = 0 ;
	outpd(ADDR(B5_XA_DA),phys) ;

	ds = (struct s_smt_fp_txd volatile *) ((char *)ds +
		HWM_ASYNC_TXD_COUNT*sizeof(struct s_smt_fp_txd)) ;
	queue = smc->hw.fp.tx[QUEUE_S] ;
	DB_GEN("Init sync TxD ring, %d TxDs ",HWM_SYNC_TXD_COUNT,0,3) ;
	(void)init_descr_ring(smc,(union s_fp_descr volatile *)ds,
		HWM_SYNC_TXD_COUNT) ;
	phys = le32_to_cpu(ds->txd_ntdadr) ;
	ds++ ;
	queue->tx_curr_put = queue->tx_curr_get = ds ;
	queue->tx_free = HWM_SYNC_TXD_COUNT ;
	queue->tx_used = 0 ;
	outpd(ADDR(B5_XS_DA),phys) ;
}