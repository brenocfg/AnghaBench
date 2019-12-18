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
 int /*<<< orphan*/  ixdp2x01_serial_device1 ; 
 int /*<<< orphan*/  ixdp2x01_serial_device2 ; 
 int /*<<< orphan*/  platform_device_register (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ixdp2x01_uart_init(void)
{
	platform_device_register(&ixdp2x01_serial_device1);
	platform_device_register(&ixdp2x01_serial_device2);
}