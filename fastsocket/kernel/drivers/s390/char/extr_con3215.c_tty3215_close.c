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
struct tty_struct {int count; int closing; scalar_t__ driver_data; } ;
struct raw3215_info {int /*<<< orphan*/  tlet; int /*<<< orphan*/ * tty; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  raw3215_shutdown (struct raw3215_info*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tty3215_close(struct tty_struct *tty, struct file * filp)
{
	struct raw3215_info *raw;

	raw = (struct raw3215_info *) tty->driver_data;
	if (raw == NULL || tty->count > 1)
		return;
	tty->closing = 1;
	/* Shutdown the terminal */
	raw3215_shutdown(raw);
	raw->tty = NULL;
	tasklet_kill(&raw->tlet);
	tty->closing = 0;
}