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
 int /*<<< orphan*/  TK_SDA_DIR (int) ; 
 int /*<<< orphan*/  TK_SDA_OUT (unsigned char) ; 
 int /*<<< orphan*/  tempudelay (int) ; 

__attribute__((used)) static void
out_byte(unsigned char x) 
{
	int i;
	TK_SDA_DIR(1);
	for (i = 8; i--;) {
		/* The chip latches incoming bits on the rising edge of SCL. */
		TK_SCL_OUT(0);
		TK_SDA_OUT(x & 1);
		tempudelay(1);
		TK_SCL_OUT(1);
		tempudelay(1);
		x >>= 1;
	}
	TK_SDA_DIR(0);
}