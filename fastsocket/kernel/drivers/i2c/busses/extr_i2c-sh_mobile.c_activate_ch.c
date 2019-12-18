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
typedef  void* u_int8_t ;
typedef  int u_int32_t ;
struct sh_mobile_i2c_data {int iccl; int icch; int /*<<< orphan*/  clk; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICCH (struct sh_mobile_i2c_data*) ; 
 int /*<<< orphan*/  ICCL (struct sh_mobile_i2c_data*) ; 
 int /*<<< orphan*/  ICCR (struct sh_mobile_i2c_data*) ; 
 int ICCR_ICE ; 
 int /*<<< orphan*/  ICIC (struct sh_mobile_i2c_data*) ; 
 int NORMAL_SPEED ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int ioread8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite8 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void activate_ch(struct sh_mobile_i2c_data *pd)
{
	unsigned long i2c_clk;
	u_int32_t num;
	u_int32_t denom;
	u_int32_t tmp;

	/* Wake up device and enable clock */
	pm_runtime_get_sync(pd->dev);
	clk_enable(pd->clk);

	/* Get clock rate after clock is enabled */
	i2c_clk = clk_get_rate(pd->clk);

	/* Calculate the value for iccl. From the data sheet:
	 * iccl = (p clock / transfer rate) * (L / (L + H))
	 * where L and H are the SCL low/high ratio (5/4 in this case).
	 * We also round off the result.
	 */
	num = i2c_clk * 5;
	denom = NORMAL_SPEED * 9;
	tmp = num * 10 / denom;
	if (tmp % 10 >= 5)
		pd->iccl = (u_int8_t)((num/denom) + 1);
	else
		pd->iccl = (u_int8_t)(num/denom);

	/* Calculate the value for icch. From the data sheet:
	   icch = (p clock / transfer rate) * (H / (L + H)) */
	num = i2c_clk * 4;
	tmp = num * 10 / denom;
	if (tmp % 10 >= 5)
		pd->icch = (u_int8_t)((num/denom) + 1);
	else
		pd->icch = (u_int8_t)(num/denom);

	/* Enable channel and configure rx ack */
	iowrite8(ioread8(ICCR(pd)) | ICCR_ICE, ICCR(pd));

	/* Mask all interrupts */
	iowrite8(0, ICIC(pd));

	/* Set the clock */
	iowrite8(pd->iccl, ICCL(pd));
	iowrite8(pd->icch, ICCH(pd));
}