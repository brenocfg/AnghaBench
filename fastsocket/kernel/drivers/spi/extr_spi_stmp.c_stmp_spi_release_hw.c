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
struct stmp_spi {TYPE_1__* master_dev; scalar_t__ clk; } ;
struct TYPE_2__ {void* platform_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (scalar_t__) ; 
 int /*<<< orphan*/  clk_disable (scalar_t__) ; 
 int /*<<< orphan*/  clk_put (scalar_t__) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int /*<<< orphan*/  stmp3xxx_release_pin_group (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stmp_spi_release_hw(struct stmp_spi *ss)
{
	void *pins = ss->master_dev->platform_data;

	if (ss->clk && !IS_ERR(ss->clk)) {
		clk_disable(ss->clk);
		clk_put(ss->clk);
	}
	stmp3xxx_release_pin_group(pins, dev_name(ss->master_dev));
}