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

/* Variables and functions */
 int /*<<< orphan*/  RFBI_CONTROL ; 
 int /*<<< orphan*/  rfbi_enable_clocks (int /*<<< orphan*/ ) ; 
 int rfbi_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfbi_write_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void _stop_transfer(void)
{
	u32 w;

	w = rfbi_read_reg(RFBI_CONTROL);
	rfbi_write_reg(RFBI_CONTROL, w & ~(1 << 0));
	rfbi_enable_clocks(0);
}