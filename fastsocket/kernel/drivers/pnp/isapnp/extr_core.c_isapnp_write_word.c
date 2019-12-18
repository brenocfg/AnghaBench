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
 int /*<<< orphan*/  isapnp_write_byte (unsigned char,unsigned short) ; 

__attribute__((used)) static void isapnp_write_word(unsigned char idx, unsigned short val)
{
	isapnp_write_byte(idx, val >> 8);
	isapnp_write_byte(idx + 1, val);
}