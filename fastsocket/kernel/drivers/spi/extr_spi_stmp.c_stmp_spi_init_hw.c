#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stmp_spi {TYPE_1__* master_dev; int /*<<< orphan*/  dma; int /*<<< orphan*/  regs; int /*<<< orphan*/  clk; } ;
struct TYPE_2__ {void* platform_data; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int /*<<< orphan*/  stmp3xxx_dma_reset_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stmp3xxx_release_pin_group (void*,int /*<<< orphan*/ ) ; 
 int stmp3xxx_request_pin_group (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stmp3xxx_reset_block (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stmp_spi_init_hw(struct stmp_spi *ss)
{
	int err = 0;
	void *pins = ss->master_dev->platform_data;

	err = stmp3xxx_request_pin_group(pins, dev_name(ss->master_dev));
	if (err)
		goto out;

	ss->clk = clk_get(NULL, "ssp");
	if (IS_ERR(ss->clk)) {
		err = PTR_ERR(ss->clk);
		goto out_free_pins;
	}
	clk_enable(ss->clk);

	stmp3xxx_reset_block(ss->regs, false);
	stmp3xxx_dma_reset_channel(ss->dma);

	return 0;

out_free_pins:
	stmp3xxx_release_pin_group(pins, dev_name(ss->master_dev));
out:
	return err;
}