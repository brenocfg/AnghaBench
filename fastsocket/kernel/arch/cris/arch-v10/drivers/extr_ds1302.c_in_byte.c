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

/* Variables and functions */
 int /*<<< orphan*/  TK_SCL_OUT (int) ; 
 int /*<<< orphan*/  TK_SDA_DIR (int /*<<< orphan*/ ) ; 
 int TK_SDA_IN () ; 
 int /*<<< orphan*/  tempudelay (int) ; 

__attribute__((used)) static unsigned char
in_byte(void) 
{
	unsigned char x = 0;
	int i;

	/* Read byte. Bits come LSB first, on the falling edge of SCL.
	 * Assume SDA is in input direction already.
	 */
	TK_SDA_DIR(0);

	for (i = 8; i--;) {
		TK_SCL_OUT(0);
		tempudelay(1);
		x >>= 1;
		x |= (TK_SDA_IN() << 7);
		TK_SCL_OUT(1);
		tempudelay(1);
	}

	return x;
}