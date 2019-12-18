#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  tx; } ;
struct TYPE_4__ {TYPE_1__ icount; } ;
struct nwpserial_port {TYPE_2__ port; int /*<<< orphan*/  dcr_host; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_LSR_THRE ; 
 int /*<<< orphan*/  UART_TX ; 
 int /*<<< orphan*/  dcr_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  wait_for_bits (struct nwpserial_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nwpserial_putchar(struct nwpserial_port *up, unsigned char c)
{
	/* check if tx buffer is full */
	wait_for_bits(up, UART_LSR_THRE);
	dcr_write(up->dcr_host, UART_TX, c);
	up->port.icount.tx++;
}