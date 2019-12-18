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
typedef  int /*<<< orphan*/  t ;
struct gpmc_timings {int cs_on; int adv_on; int sync_clk; unsigned int page_burst_access; int adv_rd_off; int oe_on; int access; int oe_off; int cs_rd_off; int adv_wr_off; int we_on; int we_off; int cs_wr_off; void* wr_cycle; void* rd_cycle; } ;

/* Variables and functions */
 int ERANGE ; 
 int gpmc_cs_set_timings (int /*<<< orphan*/ ,struct gpmc_timings*) ; 
 int /*<<< orphan*/  memset (struct gpmc_timings*,int /*<<< orphan*/ ,int) ; 
 void* next_clk (int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  sync_cs ; 

__attribute__((used)) static int tusb_set_sync_mode(unsigned sysclk_ps, unsigned fclk_ps)
{
	struct gpmc_timings	t;
	unsigned		t_scsnh_advnh = sysclk_ps + 3000;
	unsigned		tmp;

	memset(&t, 0, sizeof(t));
	t.cs_on = 8;

	/* ADV_ON = t_acsnh_advnh - t_advn */
	t.adv_on = next_clk(t.cs_on, t_scsnh_advnh - 7000, fclk_ps);

	/* GPMC_CLK rate = fclk rate / div */
	t.sync_clk = 12 /* 11.1 nsec */;
	tmp = (t.sync_clk * 1000 + fclk_ps - 1) / fclk_ps;
	if (tmp > 4)
		return -ERANGE;
	if (tmp <= 0)
		tmp = 1;
	t.page_burst_access = (fclk_ps * tmp) / 1000;

	/*
	 * READ ... based on omap2420 TRM fig 12-19, 12-20
	 */

	/* ADV_RD_OFF = t_scsnh_advnh */
	t.adv_rd_off = next_clk(t.adv_on, t_scsnh_advnh, fclk_ps);

	/* OE_ON = t_scsnh_advnh + t_advn_oen * fclk_ps (then wait for nRDY) */
	tmp = (t.adv_rd_off * 1000) + (3 * fclk_ps);
	t.oe_on = next_clk(t.adv_on, tmp, fclk_ps);

	/* ACCESS = number of clock cycles after t_adv_eon */
	tmp = (t.oe_on * 1000) + (5 * fclk_ps);
	t.access = next_clk(t.oe_on, tmp, fclk_ps);

	/* OE_OFF = after data gets sampled */
	tmp = (t.access * 1000) + (1 * fclk_ps);
	t.oe_off = next_clk(t.access, tmp, fclk_ps);

	t.cs_rd_off = t.oe_off;

	tmp = t.cs_rd_off * 1000 + 7000 /* t_scsn_rdy_z */;
	t.rd_cycle = next_clk(t.cs_rd_off, tmp, fclk_ps);

	/*
	 * WRITE ... based on omap2420 TRM fig 12-21
	 */

	/* ADV_WR_OFF = t_scsnh_advnh */
	t.adv_wr_off = t.adv_rd_off;

	/* WE_ON = t_scsnh_advnh + t_advn_wen * fclk_ps (then wait for nRDY) */
	tmp = (t.adv_wr_off * 1000) + (3 * fclk_ps);
	t.we_on = next_clk(t.adv_wr_off, tmp, fclk_ps);

	/* WE_OFF = number of clock cycles after t_adv_wen */
	tmp = (t.we_on * 1000) + (6 * fclk_ps);
	t.we_off = next_clk(t.we_on, tmp, fclk_ps);

	t.cs_wr_off = t.we_off;

	tmp = t.cs_wr_off * 1000 + 7000 /* t_scsn_rdy_z */;
	t.wr_cycle = next_clk(t.cs_wr_off, tmp, fclk_ps);

	return gpmc_cs_set_timings(sync_cs, &t);
}