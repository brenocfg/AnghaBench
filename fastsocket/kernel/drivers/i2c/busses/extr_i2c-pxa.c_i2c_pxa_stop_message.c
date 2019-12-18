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
struct pxa_i2c {int dummy; } ;

/* Variables and functions */
 int ICR_ACKNAK ; 
 int ICR_STOP ; 
 int /*<<< orphan*/  _ICR (struct pxa_i2c*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void i2c_pxa_stop_message(struct pxa_i2c *i2c)
{
	u32 icr;

	/*
	 * Clear the STOP and ACK flags
	 */
	icr = readl(_ICR(i2c));
	icr &= ~(ICR_STOP | ICR_ACKNAK);
	writel(icr, _ICR(i2c));
}