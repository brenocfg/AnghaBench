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
struct raw3270 {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  RAW3270_FLAGS_14BITADDR ; 
 char* raw3270_ebcgraf ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
raw3270_buffer_address(struct raw3270 *rp, char *cp, unsigned short addr)
{
	if (test_bit(RAW3270_FLAGS_14BITADDR, &rp->flags)) {
		cp[0] = (addr >> 8) & 0x3f;
		cp[1] = addr & 0xff;
	} else {
		cp[0] = raw3270_ebcgraf[(addr >> 6) & 0x3f];
		cp[1] = raw3270_ebcgraf[addr & 0x3f];
	}
}