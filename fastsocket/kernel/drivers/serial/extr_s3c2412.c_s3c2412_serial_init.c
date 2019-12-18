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

/* Variables and functions */
 int /*<<< orphan*/  s3c2412_serial_driver ; 
 int /*<<< orphan*/  s3c2412_uart_inf ; 
 int s3c24xx_serial_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int s3c2412_serial_init(void)
{
	return s3c24xx_serial_init(&s3c2412_serial_driver, &s3c2412_uart_inf);
}