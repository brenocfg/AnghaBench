#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct dbg_port {int started; int nbr; int baudrate; char parity; int bits; int /*<<< orphan*/  instance; } ;
struct TYPE_7__ {int en; int dma_mode; int div; void* data_bits; void* par; void* par_en; int /*<<< orphan*/  base_freq; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ reg_ser_rw_tr_dma_en ;
typedef  TYPE_1__ reg_ser_rw_tr_ctrl ;
typedef  TYPE_1__ reg_ser_rw_tr_baud_div ;
typedef  TYPE_1__ reg_ser_rw_rec_ctrl ;
typedef  TYPE_1__ reg_ser_rw_rec_baud_div ;

/* Variables and functions */
 int /*<<< orphan*/  REG_WR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__) ; 
 int /*<<< orphan*/  crisv32_pinmux_alloc_fixed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pinmux_ser1 ; 
 int /*<<< orphan*/  pinmux_ser2 ; 
 int /*<<< orphan*/  pinmux_ser3 ; 
 int /*<<< orphan*/  pinmux_ser4 ; 
 void* regk_ser_bits7 ; 
 void* regk_ser_even ; 
 int /*<<< orphan*/  regk_ser_f29_493 ; 
 int regk_ser_no ; 
 void* regk_ser_odd ; 
 void* regk_ser_yes ; 
 int /*<<< orphan*/  rw_rec_baud_div ; 
 int /*<<< orphan*/  rw_rec_ctrl ; 
 int /*<<< orphan*/  rw_tr_baud_div ; 
 int /*<<< orphan*/  rw_tr_ctrl ; 
 int /*<<< orphan*/  rw_tr_dma_en ; 
 int /*<<< orphan*/  ser ; 

__attribute__((used)) static void
start_port(struct dbg_port* p)
{
	if (!p)
		return;

	if (p->started)
		return;
	p->started = 1;

	if (p->nbr == 1)
		crisv32_pinmux_alloc_fixed(pinmux_ser1);
	else if (p->nbr == 2)
		crisv32_pinmux_alloc_fixed(pinmux_ser2);
	else if (p->nbr == 3)
		crisv32_pinmux_alloc_fixed(pinmux_ser3);
#if CONFIG_ETRAX_SERIAL_PORTS == 5
	else if (p->nbr == 4)
		crisv32_pinmux_alloc_fixed(pinmux_ser4);
#endif

	/* Set up serial port registers */
	reg_ser_rw_tr_ctrl tr_ctrl = {0};
	reg_ser_rw_tr_dma_en tr_dma_en = {0};

	reg_ser_rw_rec_ctrl rec_ctrl = {0};
	reg_ser_rw_tr_baud_div tr_baud_div = {0};
	reg_ser_rw_rec_baud_div rec_baud_div = {0};

	tr_ctrl.base_freq = rec_ctrl.base_freq = regk_ser_f29_493;
	tr_dma_en.en = rec_ctrl.dma_mode = regk_ser_no;
	tr_baud_div.div = rec_baud_div.div = 29493000 / p->baudrate / 8;
	tr_ctrl.en = rec_ctrl.en = 1;

	if (p->parity == 'O')
	{
		tr_ctrl.par_en = regk_ser_yes;
		tr_ctrl.par = regk_ser_odd;
		rec_ctrl.par_en = regk_ser_yes;
		rec_ctrl.par = regk_ser_odd;
	}
	else if (p->parity == 'E')
	{
		tr_ctrl.par_en = regk_ser_yes;
		tr_ctrl.par = regk_ser_even;
		rec_ctrl.par_en = regk_ser_yes;
		rec_ctrl.par = regk_ser_odd;
	}

	if (p->bits == 7)
	{
		tr_ctrl.data_bits = regk_ser_bits7;
		rec_ctrl.data_bits = regk_ser_bits7;
	}

	REG_WR (ser, p->instance, rw_tr_baud_div, tr_baud_div);
	REG_WR (ser, p->instance, rw_rec_baud_div, rec_baud_div);
	REG_WR (ser, p->instance, rw_tr_dma_en, tr_dma_en);
	REG_WR (ser, p->instance, rw_tr_ctrl, tr_ctrl);
	REG_WR (ser, p->instance, rw_rec_ctrl, rec_ctrl);
}