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
struct serial_console_data {char (* getc ) () ;int /*<<< orphan*/  (* putc ) (char) ;scalar_t__ (* tstc ) () ;} ;
struct TYPE_2__ {struct serial_console_data* data; } ;

/* Variables and functions */
 TYPE_1__ console_ops ; 
 int /*<<< orphan*/  printf (char*) ; 
 int strlen (char*) ; 
 scalar_t__ stub1 () ; 
 char stub2 () ; 
 int /*<<< orphan*/  stub3 (char) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void serial_edit_cmdline(char *buf, int len)
{
	int timer = 0, count;
	char ch, *cp;
	struct serial_console_data *scdp = console_ops.data;

	cp = buf;
	count = strlen(buf);
	cp = &buf[count];
	count++;

	while (timer++ < 5*1000) {
		if (scdp->tstc()) {
			while (((ch = scdp->getc()) != '\n') && (ch != '\r')) {
				/* Test for backspace/delete */
				if ((ch == '\b') || (ch == '\177')) {
					if (cp != buf) {
						cp--;
						count--;
						printf("\b \b");
					}
				/* Test for ^x/^u (and wipe the line) */
				} else if ((ch == '\030') || (ch == '\025')) {
					while (cp != buf) {
						cp--;
						count--;
						printf("\b \b");
					}
				} else if (count < len) {
						*cp++ = ch;
						count++;
						scdp->putc(ch);
				}
			}
			break;  /* Exit 'timer' loop */
		}
		udelay(1000);  /* 1 msec */
	}
	*cp = 0;
}