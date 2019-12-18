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
struct uart_state {int /*<<< orphan*/  xmit; int /*<<< orphan*/  uart_port; } ;
struct tty_struct {struct uart_state* driver_data; } ;

/* Variables and functions */
 int __uart_put_char (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char) ; 

__attribute__((used)) static int uart_put_char(struct tty_struct *tty, unsigned char ch)
{
	struct uart_state *state = tty->driver_data;

	return __uart_put_char(state->uart_port, &state->xmit, ch);
}