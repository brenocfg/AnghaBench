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
 int ICR_TB ; 
 int ISR_BED ; 
 int /*<<< orphan*/  _ICR (struct pxa_i2c*) ; 
 int /*<<< orphan*/  _IDBR (struct pxa_i2c*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i2c_pxa_slave_txempty(struct pxa_i2c *i2c, u32 isr)
{
	if (isr & ISR_BED) {
		/* what should we do here? */
	} else {
		writel(0, _IDBR(i2c));
		writel(readl(_ICR(i2c)) | ICR_TB, _ICR(i2c));
	}
}