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
struct tty_driver {char* driver_name; int num; int type; scalar_t__ subtype; int /*<<< orphan*/  name; } ;
struct seq_file {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int MAJOR (int /*<<< orphan*/ ) ; 
 scalar_t__ MINOR (int /*<<< orphan*/ ) ; 
 scalar_t__ PTY_TYPE_MASTER ; 
 scalar_t__ PTY_TYPE_SLAVE ; 
 scalar_t__ SYSTEM_TYPE_CONSOLE ; 
 scalar_t__ SYSTEM_TYPE_SYSCONS ; 
 scalar_t__ SYSTEM_TYPE_TTY ; 
#define  TTY_DRIVER_TYPE_CONSOLE 131 
#define  TTY_DRIVER_TYPE_PTY 130 
#define  TTY_DRIVER_TYPE_SERIAL 129 
#define  TTY_DRIVER_TYPE_SYSTEM 128 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 

__attribute__((used)) static void show_tty_range(struct seq_file *m, struct tty_driver *p,
	dev_t from, int num)
{
	seq_printf(m, "%-20s ", p->driver_name ? p->driver_name : "unknown");
	seq_printf(m, "/dev/%-8s ", p->name);
	if (p->num > 1) {
		seq_printf(m, "%3d %d-%d ", MAJOR(from), MINOR(from),
			MINOR(from) + num - 1);
	} else {
		seq_printf(m, "%3d %7d ", MAJOR(from), MINOR(from));
	}
	switch (p->type) {
	case TTY_DRIVER_TYPE_SYSTEM:
		seq_printf(m, "system");
		if (p->subtype == SYSTEM_TYPE_TTY)
			seq_printf(m, ":/dev/tty");
		else if (p->subtype == SYSTEM_TYPE_SYSCONS)
			seq_printf(m, ":console");
		else if (p->subtype == SYSTEM_TYPE_CONSOLE)
			seq_printf(m, ":vtmaster");
		break;
	case TTY_DRIVER_TYPE_CONSOLE:
		seq_printf(m, "console");
		break;
	case TTY_DRIVER_TYPE_SERIAL:
		seq_printf(m, "serial");
		break;
	case TTY_DRIVER_TYPE_PTY:
		if (p->subtype == PTY_TYPE_MASTER)
			seq_printf(m, "pty:master");
		else if (p->subtype == PTY_TYPE_SLAVE)
			seq_printf(m, "pty:slave");
		else
			seq_printf(m, "pty");
		break;
	default:
		seq_printf(m, "type:%d.%d", p->type, p->subtype);
	}
	seq_putc(m, '\n');
}