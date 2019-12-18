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
struct sge {int starve_thres; int /*<<< orphan*/  intrq_lock; scalar_t__* idma_state; int /*<<< orphan*/  tx_timer; int /*<<< orphan*/  rx_timer; int /*<<< orphan*/ * timer_val; int /*<<< orphan*/ * counter_val; } ;
struct adapter {struct sge sge; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_SGE_DBFIFO_STATUS ; 
 int /*<<< orphan*/  A_SGE_DOORBELL_CONTROL ; 
 int EGRSTATUSPAGESIZE ; 
 int /*<<< orphan*/  FL_ALIGN ; 
 unsigned int FL_PG_ORDER ; 
 int F_ENABLE_DROP ; 
 int INGPADBOUNDARY (unsigned int) ; 
 int INGPADBOUNDARY_MASK ; 
 int /*<<< orphan*/  M_HP_INT_THRESH ; 
 int /*<<< orphan*/  M_LP_INT_THRESH ; 
 int PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 int PKTSHIFT (int) ; 
 int PKTSHIFT_MASK ; 
 int RXPKTCPLMODE ; 
 int /*<<< orphan*/  SGE_CONTROL ; 
 int /*<<< orphan*/  SGE_FL_BUFFER_SIZE0 ; 
 int /*<<< orphan*/  SGE_FL_BUFFER_SIZE1 ; 
 int /*<<< orphan*/  SGE_HOST_PAGE_SIZE ; 
 int /*<<< orphan*/  SGE_INGRESS_RX_THRESHOLD ; 
 int /*<<< orphan*/  SGE_TIMER_VALUE_0_AND_1 ; 
 int /*<<< orphan*/  SGE_TIMER_VALUE_2_AND_3 ; 
 int /*<<< orphan*/  SGE_TIMER_VALUE_4_AND_5 ; 
 int STAT_LEN ; 
 unsigned int THRESHOLD_0 (int /*<<< orphan*/ ) ; 
 unsigned int THRESHOLD_1 (int /*<<< orphan*/ ) ; 
 unsigned int THRESHOLD_2 (int /*<<< orphan*/ ) ; 
 unsigned int THRESHOLD_3 (int /*<<< orphan*/ ) ; 
 unsigned int TIMERVALUE0 (int /*<<< orphan*/ ) ; 
 unsigned int TIMERVALUE1 (int /*<<< orphan*/ ) ; 
 int V_HP_INT_THRESH (int /*<<< orphan*/ ) ; 
 int V_LP_INT_THRESH (int /*<<< orphan*/ ) ; 
 int core_ticks_per_usec (struct adapter*) ; 
 int /*<<< orphan*/  dbfifo_int_thresh ; 
 unsigned int ilog2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  sge_rx_timer_cb ; 
 int /*<<< orphan*/  sge_tx_timer_cb ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t4_set_reg_field (struct adapter*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  us_to_core_ticks (struct adapter*,int /*<<< orphan*/ ) ; 

void t4_sge_init(struct adapter *adap)
{
	unsigned int i, v;
	struct sge *s = &adap->sge;
	unsigned int fl_align_log = ilog2(FL_ALIGN);

	t4_set_reg_field(adap, SGE_CONTROL, PKTSHIFT_MASK |
			 INGPADBOUNDARY_MASK | EGRSTATUSPAGESIZE,
			 INGPADBOUNDARY(fl_align_log - 5) | PKTSHIFT(2) |
			 RXPKTCPLMODE |
			 (STAT_LEN == 128 ? EGRSTATUSPAGESIZE : 0));

	t4_set_reg_field(adap, A_SGE_DBFIFO_STATUS,
			V_HP_INT_THRESH(M_HP_INT_THRESH) |
			V_LP_INT_THRESH(M_LP_INT_THRESH),
			V_HP_INT_THRESH(dbfifo_int_thresh) |
			V_LP_INT_THRESH(dbfifo_int_thresh));
	t4_set_reg_field(adap, A_SGE_DOORBELL_CONTROL, F_ENABLE_DROP,
			F_ENABLE_DROP);

	for (i = v = 0; i < 32; i += 4)
		v |= (PAGE_SHIFT - 10) << i;
	t4_write_reg(adap, SGE_HOST_PAGE_SIZE, v);
	t4_write_reg(adap, SGE_FL_BUFFER_SIZE0, PAGE_SIZE);
#if FL_PG_ORDER > 0
	t4_write_reg(adap, SGE_FL_BUFFER_SIZE1, PAGE_SIZE << FL_PG_ORDER);
#endif
	t4_write_reg(adap, SGE_INGRESS_RX_THRESHOLD,
		     THRESHOLD_0(s->counter_val[0]) |
		     THRESHOLD_1(s->counter_val[1]) |
		     THRESHOLD_2(s->counter_val[2]) |
		     THRESHOLD_3(s->counter_val[3]));
	t4_write_reg(adap, SGE_TIMER_VALUE_0_AND_1,
		     TIMERVALUE0(us_to_core_ticks(adap, s->timer_val[0])) |
		     TIMERVALUE1(us_to_core_ticks(adap, s->timer_val[1])));
	t4_write_reg(adap, SGE_TIMER_VALUE_2_AND_3,
		     TIMERVALUE0(us_to_core_ticks(adap, s->timer_val[2])) |
		     TIMERVALUE1(us_to_core_ticks(adap, s->timer_val[3])));
	t4_write_reg(adap, SGE_TIMER_VALUE_4_AND_5,
		     TIMERVALUE0(us_to_core_ticks(adap, s->timer_val[4])) |
		     TIMERVALUE1(us_to_core_ticks(adap, s->timer_val[5])));
	setup_timer(&s->rx_timer, sge_rx_timer_cb, (unsigned long)adap);
	setup_timer(&s->tx_timer, sge_tx_timer_cb, (unsigned long)adap);
	s->starve_thres = core_ticks_per_usec(adap) * 1000000;  /* 1 s */
	s->idma_state[0] = s->idma_state[1] = 0;
	spin_lock_init(&s->intrq_lock);
}