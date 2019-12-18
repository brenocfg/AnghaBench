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
struct TYPE_2__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 TYPE_1__* m32r_sio_ports ; 
 int /*<<< orphan*/  m32r_sio_reg ; 
 int /*<<< orphan*/  uart_resume_port (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void m32r_sio_resume_port(int line)
{
	uart_resume_port(&m32r_sio_reg, &m32r_sio_ports[line].port);
}