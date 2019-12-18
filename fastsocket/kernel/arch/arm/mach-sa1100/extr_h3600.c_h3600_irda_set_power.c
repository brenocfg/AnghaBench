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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPAQ_EGPIO_IR_ON ; 
 int /*<<< orphan*/  assign_h3600_egpio (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int h3600_irda_set_power(struct device *dev, unsigned int state)
{
	assign_h3600_egpio( IPAQ_EGPIO_IR_ON, state );

	return 0;
}