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
typedef  int u32 ;
struct TYPE_2__ {int bits_per_cycle; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  RFBI_CONFIG0 ; 
 TYPE_1__ rfbi ; 
 int /*<<< orphan*/  rfbi_enable_clocks (int) ; 
 int rfbi_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfbi_write_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rfbi_set_bits_per_cycle(int bpc)
{
	u32 l;

	rfbi_enable_clocks(1);
	l = rfbi_read_reg(RFBI_CONFIG0);
	l &= ~(0x03 << 0);

	switch (bpc) {
	case 8:
		break;
	case 16:
		l |= 3;
		break;
	default:
		BUG();
	}
	rfbi_write_reg(RFBI_CONFIG0, l);
	rfbi.bits_per_cycle = bpc;
	rfbi_enable_clocks(0);
}