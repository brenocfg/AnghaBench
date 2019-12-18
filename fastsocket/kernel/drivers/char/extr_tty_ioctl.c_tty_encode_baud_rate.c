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
struct tty_struct {int /*<<< orphan*/  termios; } ;
typedef  int /*<<< orphan*/  speed_t ;

/* Variables and functions */
 int /*<<< orphan*/  tty_termios_encode_baud_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void tty_encode_baud_rate(struct tty_struct *tty, speed_t ibaud, speed_t obaud)
{
	tty_termios_encode_baud_rate(tty->termios, ibaud, obaud);
}