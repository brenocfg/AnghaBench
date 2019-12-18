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
 int /*<<< orphan*/  RS5C313_ADDR_CNTREG ; 
 int /*<<< orphan*/  rs5c313_write_reg (int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static inline void rs5c313_write_cntreg(unsigned char data)
{
	rs5c313_write_reg(RS5C313_ADDR_CNTREG, data);
}