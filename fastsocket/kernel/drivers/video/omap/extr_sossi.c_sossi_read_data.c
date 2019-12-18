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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  fck; int /*<<< orphan*/  bus_pick_width; int /*<<< orphan*/  bus_pick_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  RD_ACCESS ; 
 int /*<<< orphan*/  SOSSI_FIFO_REG ; 
 int /*<<< orphan*/  SOSSI_INIT1_REG ; 
 int /*<<< orphan*/  _set_bits_per_cycle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cycles (unsigned int) ; 
 int /*<<< orphan*/  set_timing (int /*<<< orphan*/ ) ; 
 TYPE_1__ sossi ; 
 int /*<<< orphan*/  sossi_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sossi_read_reg16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sossi_read_reg8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sossi_set_bits (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sossi_start_transfer () ; 
 int /*<<< orphan*/  sossi_stop_transfer () ; 

__attribute__((used)) static void sossi_read_data(void *data, unsigned int len)
{
	clk_enable(sossi.fck);
	set_timing(RD_ACCESS);
	_set_bits_per_cycle(sossi.bus_pick_count, sossi.bus_pick_width);
	/* CMD#/DATA */
	sossi_set_bits(SOSSI_INIT1_REG, 1 << 18);
	set_cycles(len);
	sossi_start_transfer();
	while (len >= 4) {
		*(u32 *) data = sossi_read_reg(SOSSI_FIFO_REG);
		len -= 4;
		data += 4;
	}
	while (len >= 2) {
		*(u16 *) data = sossi_read_reg16(SOSSI_FIFO_REG);
		len -= 2;
		data += 2;
	}
	while (len) {
		*(u8 *) data = sossi_read_reg8(SOSSI_FIFO_REG);
		len--;
		data++;
	}
	sossi_stop_transfer();
	clk_disable(sossi.fck);
}