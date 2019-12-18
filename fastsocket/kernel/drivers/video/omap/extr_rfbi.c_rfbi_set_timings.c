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
typedef  int u32 ;
struct extif_timings {int* tim; int /*<<< orphan*/  converted; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  RFBI_CONFIG0 ; 
 int /*<<< orphan*/  RFBI_CYCLE_TIME0 ; 
 int /*<<< orphan*/  RFBI_ONOFF_TIME0 ; 
 int /*<<< orphan*/  rfbi_enable_clocks (int) ; 
 int /*<<< orphan*/  rfbi_print_timings () ; 
 int rfbi_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfbi_write_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rfbi_set_timings(const struct extif_timings *t)
{
	u32 l;

	BUG_ON(!t->converted);

	rfbi_enable_clocks(1);
	rfbi_write_reg(RFBI_ONOFF_TIME0, t->tim[0]);
	rfbi_write_reg(RFBI_CYCLE_TIME0, t->tim[1]);

	l = rfbi_read_reg(RFBI_CONFIG0);
	l &= ~(1 << 4);
	l |= (t->tim[2] ? 1 : 0) << 4;
	rfbi_write_reg(RFBI_CONFIG0, l);

	rfbi_print_timings();
	rfbi_enable_clocks(0);
}