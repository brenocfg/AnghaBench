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
struct uart_port {int dummy; } ;
struct serial_struct {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int sunzilog_verify_port(struct uart_port *port, struct serial_struct *ser)
{
	return -EINVAL;
}