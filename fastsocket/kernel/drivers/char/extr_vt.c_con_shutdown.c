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
struct vc_data {int /*<<< orphan*/ * vc_tty; } ;
struct tty_struct {struct vc_data* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acquire_console_sem () ; 
 int /*<<< orphan*/  release_console_sem () ; 
 int /*<<< orphan*/  tty_shutdown (struct tty_struct*) ; 

__attribute__((used)) static void con_shutdown(struct tty_struct *tty)
{
	struct vc_data *vc = tty->driver_data;
	BUG_ON(vc == NULL);
	acquire_console_sem();
	vc->vc_tty = NULL;
	release_console_sem();
	tty_shutdown(tty);
}