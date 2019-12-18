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
struct pxa_i2c {int dummy; } ;

/* Variables and functions */
 int DEF_TIMEOUT ; 
 int I2C_RETRY ; 
 int ISR_IBB ; 
 int ISR_SAD ; 
 int ISR_UB ; 
 int /*<<< orphan*/  _ISR (struct pxa_i2c*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_state (struct pxa_i2c*) ; 

__attribute__((used)) static int i2c_pxa_wait_bus_not_busy(struct pxa_i2c *i2c)
{
	int timeout = DEF_TIMEOUT;

	while (timeout-- && readl(_ISR(i2c)) & (ISR_IBB | ISR_UB)) {
		if ((readl(_ISR(i2c)) & ISR_SAD) != 0)
			timeout += 4;

		msleep(2);
		show_state(i2c);
	}

	if (timeout < 0)
		show_state(i2c);

	return timeout < 0 ? I2C_RETRY : 0;
}