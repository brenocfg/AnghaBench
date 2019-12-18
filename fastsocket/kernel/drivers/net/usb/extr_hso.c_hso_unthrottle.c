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
struct tty_struct {int dummy; } ;
struct hso_serial {int /*<<< orphan*/  unthrottle_tasklet; } ;

/* Variables and functions */
 struct hso_serial* get_serial_by_tty (struct tty_struct*) ; 
 int /*<<< orphan*/  tasklet_hi_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static	void hso_unthrottle(struct tty_struct *tty)
{
	struct hso_serial *serial = get_serial_by_tty(tty);

	tasklet_hi_schedule(&serial->unthrottle_tasklet);
}