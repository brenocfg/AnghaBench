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
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S3C_PCLK_GATE ; 
 int s3c64xx_gate (int /*<<< orphan*/ ,struct clk*,int) ; 

__attribute__((used)) static int s3c64xx_pclk_ctrl(struct clk *clk, int enable)
{
	return s3c64xx_gate(S3C_PCLK_GATE, clk, enable);
}