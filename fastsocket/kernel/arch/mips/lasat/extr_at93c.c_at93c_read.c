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
typedef  int u8 ;

/* Variables and functions */
 int AT93C_ADDR_MAX ; 
 int AT93C_RCMD ; 
 int /*<<< orphan*/  at93c_end_op () ; 
 int /*<<< orphan*/  at93c_init_op () ; 
 int at93c_read_byte () ; 
 int /*<<< orphan*/  at93c_write_bits (int,int) ; 

u8 at93c_read(u8 addr)
{
	u8 byte;
	at93c_init_op();
	at93c_write_bits((addr & AT93C_ADDR_MAX)|AT93C_RCMD, 10);
	byte = at93c_read_byte();
	at93c_end_op();
	return byte;
}