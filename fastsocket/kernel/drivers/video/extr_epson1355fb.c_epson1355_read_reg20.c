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
typedef  int u32 ;
struct epson1355_par {int dummy; } ;

/* Variables and functions */
 int epson1355_read_reg (struct epson1355_par*,int) ; 

__attribute__((used)) static inline u32 epson1355_read_reg20(struct epson1355_par *par, int index)
{
	u8 b0 = epson1355_read_reg(par, index);
	u8 b1 = epson1355_read_reg(par, index + 1);
	u8 b2 = epson1355_read_reg(par, index + 2);

	return (b2 & 0x0f) << 16 | (b1 << 8) | b0;
}