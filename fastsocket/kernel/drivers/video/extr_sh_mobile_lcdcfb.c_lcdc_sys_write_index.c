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
 int /*<<< orphan*/  _LDDWAR ; 
 int /*<<< orphan*/  _LDDWD0R ; 
 int /*<<< orphan*/  _LDSR ; 
 scalar_t__ lcdc_chan_is_sublcd (struct sh_mobile_lcdc_chan*) ; 
 int /*<<< orphan*/  lcdc_wait_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcdc_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lcdc_sys_write_index(void *handle, unsigned long data)
{
	struct sh_mobile_lcdc_chan *ch = handle;

	lcdc_write(ch->lcdc, _LDDWD0R, data | 0x10000000);
	lcdc_wait_bit(ch->lcdc, _LDSR, 2, 0);
	lcdc_write(ch->lcdc, _LDDWAR, 1 | (lcdc_chan_is_sublcd(ch) ? 2 : 0));
	lcdc_wait_bit(ch->lcdc, _LDSR, 2, 0);
}