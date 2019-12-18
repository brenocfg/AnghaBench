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
struct s_smt_rx_queue {scalar_t__ rx_used; int /*<<< orphan*/  rx_free; struct s_smt_fp_rxd volatile* rx_curr_get; struct s_smt_fp_rxd volatile* rx_curr_put; } ;
struct s_smt_fp_rxd {int /*<<< orphan*/  rxd_nrdadr; } ;
struct TYPE_5__ {struct s_smt_rx_queue** rx; } ;
struct TYPE_6__ {TYPE_1__ fp; } ;
struct TYPE_7__ {scalar_t__ descr_p; } ;
struct TYPE_8__ {TYPE_3__ hwm; } ;
struct s_smc {TYPE_2__ hw; TYPE_4__ os; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B4_R1_DA ; 
 int /*<<< orphan*/  DB_GEN (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 size_t QUEUE_R1 ; 
 int /*<<< orphan*/  SMT_R1_RXD_COUNT ; 
 int /*<<< orphan*/  init_descr_ring (struct s_smc*,union s_fp_descr volatile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outpd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_rxd_ring(struct s_smc *smc)
{
	struct s_smt_fp_rxd volatile *ds ;
	struct s_smt_rx_queue *queue ;
	u_long	phys ;

	/*
	 * initialize the receive descriptors
	 */
	ds = (struct s_smt_fp_rxd volatile *) smc->os.hwm.descr_p ;
	queue = smc->hw.fp.rx[QUEUE_R1] ;
	DB_GEN("Init RxD ring, %d RxDs ",SMT_R1_RXD_COUNT,0,3) ;
	(void)init_descr_ring(smc,(union s_fp_descr volatile *)ds,
		SMT_R1_RXD_COUNT) ;
	phys = le32_to_cpu(ds->rxd_nrdadr) ;
	ds++ ;
	queue->rx_curr_put = queue->rx_curr_get = ds ;
	queue->rx_free = SMT_R1_RXD_COUNT ;
	queue->rx_used = 0 ;
	outpd(ADDR(B4_R1_DA),phys) ;
}