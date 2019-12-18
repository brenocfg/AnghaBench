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
 int /*<<< orphan*/  UART_MODE_ON ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart6850_cmd (int /*<<< orphan*/ ) ; 
 scalar_t__ uart6850_opened ; 
 int /*<<< orphan*/  uart6850_timer ; 

__attribute__((used)) static void uart6850_close(int dev)
{
	uart6850_cmd(UART_MODE_ON);
	del_timer(&uart6850_timer);
	uart6850_opened = 0;
}