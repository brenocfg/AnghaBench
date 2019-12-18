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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int bits_per_cycle; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  RFBI_READ ; 
 TYPE_1__ rfbi ; 
 int /*<<< orphan*/  rfbi_enable_clocks (int) ; 
 void* rfbi_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfbi_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rfbi_read_data(void *buf, unsigned int len)
{
	rfbi_enable_clocks(1);
	if (rfbi.bits_per_cycle == 16) {
		u16 *w = buf;
		BUG_ON(len & ~1);
		for (; len; len -= 2) {
			rfbi_write_reg(RFBI_READ, 0);
			*w++ = rfbi_read_reg(RFBI_READ);
		}
	} else {
		u8 *b = buf;
		BUG_ON(rfbi.bits_per_cycle != 8);
		for (; len; len--) {
			rfbi_write_reg(RFBI_READ, 0);
			*b++ = rfbi_read_reg(RFBI_READ);
		}
	}
	rfbi_enable_clocks(0);
}