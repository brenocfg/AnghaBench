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
 int /*<<< orphan*/  WRITE_REGISTER ; 
 int /*<<< orphan*/  b1_put_byte (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b1_put_word (unsigned int,unsigned int) ; 

__attribute__((used)) static void b1_wr_reg(unsigned int base,
                      unsigned int reg,
		      unsigned int value)
{
	b1_put_byte(base, WRITE_REGISTER);
        b1_put_word(base, reg);
        b1_put_word(base, value);
}