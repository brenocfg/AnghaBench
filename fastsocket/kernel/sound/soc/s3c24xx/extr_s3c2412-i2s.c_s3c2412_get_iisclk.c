#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct clk {int dummy; } ;
struct TYPE_2__ {struct clk* iis_clk; } ;

/* Variables and functions */
 TYPE_1__ s3c2412_i2s ; 

struct clk *s3c2412_get_iisclk(void)
{
	return s3c2412_i2s.iis_clk;
}