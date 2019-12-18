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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  s3c2400_uart_inf ; 
 int s3c24xx_serial_probe (struct platform_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int s3c2400_serial_probe(struct platform_device *dev)
{
	return s3c24xx_serial_probe(dev, &s3c2400_uart_inf);
}