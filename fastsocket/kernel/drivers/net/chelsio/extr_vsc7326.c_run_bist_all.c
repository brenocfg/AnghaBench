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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  REG_DEV_SETUP (int) ; 
 int /*<<< orphan*/  REG_MEM_BIST ; 
 int /*<<< orphan*/  REG_SPI4_MISC ; 
 int /*<<< orphan*/  check_bist (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  enable_mem (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  run_bist (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  vsc_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vsc_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int run_bist_all(adapter_t *adapter)
{
	int port = 0;
	u32 val = 0;

	vsc_write(adapter, REG_MEM_BIST, 0x5);
	vsc_read(adapter, REG_MEM_BIST, &val);

	for (port = 0; port < 12; port++)
		vsc_write(adapter, REG_DEV_SETUP(port), 0x0);

	udelay(300);
	vsc_write(adapter, REG_SPI4_MISC, 0x00040409);
	udelay(300);

	(void) run_bist(adapter,13);
	(void) run_bist(adapter,14);
	(void) run_bist(adapter,20);
	(void) run_bist(adapter,21);
	mdelay(200);
	(void) check_bist(adapter,13);
	(void) check_bist(adapter,14);
	(void) check_bist(adapter,20);
	(void) check_bist(adapter,21);
	udelay(100);
	(void) enable_mem(adapter,13);
	(void) enable_mem(adapter,14);
	(void) enable_mem(adapter,20);
	(void) enable_mem(adapter,21);
	udelay(300);
	vsc_write(adapter, REG_SPI4_MISC, 0x60040400);
	udelay(300);
	for (port = 0; port < 12; port++)
		vsc_write(adapter, REG_DEV_SETUP(port), 0x1);

	udelay(300);
	vsc_write(adapter, REG_MEM_BIST, 0x0);
	mdelay(10);
	return 0;
}