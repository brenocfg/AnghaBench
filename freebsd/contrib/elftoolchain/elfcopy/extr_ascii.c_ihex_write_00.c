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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ihex_write (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ihex_write_04 (int,int) ; 

__attribute__((used)) static void
ihex_write_00(int ofd, uint64_t addr, const void *buf, size_t sz)
{
	uint16_t addr_hi, old_addr_hi;
	const uint8_t *p, *pe;

	old_addr_hi = (addr >> 16) & 0xFFFF;
	p = buf;
	pe = p + sz;
	while (pe - p >= 16) {
		ihex_write(ofd, 0, addr, 0, p, 16);
		addr += 16;
		p += 16;
		addr_hi = (addr >> 16) & 0xFFFF;
		if (addr_hi != old_addr_hi) {
			old_addr_hi = addr_hi;
			ihex_write_04(ofd, addr_hi);
		}
	}
	if (pe - p > 0)
		ihex_write(ofd, 0, addr, 0, p, pe - p);
}