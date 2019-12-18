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
typedef  int u32 ;
struct isp116x {int /*<<< orphan*/  data_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  isp116x_delay (struct isp116x*,int) ; 
 int /*<<< orphan*/  writew (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void isp116x_write_data32(struct isp116x *isp116x, u32 val)
{
	writew(val & 0xffff, isp116x->data_reg);
	isp116x_delay(isp116x, 150);
	writew(val >> 16, isp116x->data_reg);
	isp116x_delay(isp116x, 150);
}