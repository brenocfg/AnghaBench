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
typedef  int /*<<< orphan*/  u_char ;
struct sym_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLR_BIT ; 
 int /*<<< orphan*/  CLR_CLK ; 
 int /*<<< orphan*/  INB (struct sym_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S24C16_set_bit (struct sym_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_BIT ; 
 int /*<<< orphan*/  SET_CLK ; 
 int /*<<< orphan*/  nc_gpreg ; 

__attribute__((used)) static void S24C16_do_bit(struct sym_device *np, u_char *read_bit, u_char write_bit, 
			 u_char *gpreg)
{
	S24C16_set_bit(np, write_bit, gpreg, SET_BIT);
	S24C16_set_bit(np, 0, gpreg, SET_CLK);
	if (read_bit)
		*read_bit = INB(np, nc_gpreg);
	S24C16_set_bit(np, 0, gpreg, CLR_CLK);
	S24C16_set_bit(np, 0, gpreg, CLR_BIT);
}