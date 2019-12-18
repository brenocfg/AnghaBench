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
struct sh_mobile_lcdc_chan {int /*<<< orphan*/  lcdc; } ;

/* Variables and functions */
 int /*<<< orphan*/  _LDDRAR ; 
 int /*<<< orphan*/  _LDDRDR ; 
 int /*<<< orphan*/  _LDSR ; 
 scalar_t__ lcdc_chan_is_sublcd (struct sh_mobile_lcdc_chan*) ; 
 int lcdc_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcdc_wait_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcdc_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static unsigned long lcdc_sys_read_data(void *handle)
{
	struct sh_mobile_lcdc_chan *ch = handle;

	lcdc_write(ch->lcdc, _LDDRDR, 0x01000000);
	lcdc_wait_bit(ch->lcdc, _LDSR, 2, 0);
	lcdc_write(ch->lcdc, _LDDRAR, 1 | (lcdc_chan_is_sublcd(ch) ? 2 : 0));
	udelay(1);
	lcdc_wait_bit(ch->lcdc, _LDSR, 2, 0);

	return lcdc_read(ch->lcdc, _LDDRDR) & 0x3ffff;
}