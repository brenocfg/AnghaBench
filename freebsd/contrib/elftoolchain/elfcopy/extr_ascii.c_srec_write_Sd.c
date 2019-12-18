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
typedef  size_t uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  srec_write (int,char,size_t,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void
srec_write_Sd(int ofd, char dr, uint64_t addr, const void *buf, size_t sz,
    size_t rlen)
{
	const uint8_t *p, *pe;

	p = buf;
	pe = p + sz;
	while (pe - p >= (int) rlen) {
		srec_write(ofd, dr, addr, p, rlen);
		addr += rlen;
		p += rlen;
	}
	if (pe - p > 0)
		srec_write(ofd, dr, addr, p, pe - p);
}