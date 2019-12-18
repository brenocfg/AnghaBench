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
struct console {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdbstub_send_packet (char*) ; 
 int /*<<< orphan*/  mem2hex (char const*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __gdbstub_console_write(struct console *co, const char *p, unsigned n)
{
	char outbuf[26];
	int qty;

	outbuf[0] = 'O';

	while (n > 0) {
		qty = 1;

		while (n > 0 && qty < 20) {
			mem2hex(p, outbuf + qty, 2, 0);
			qty += 2;
			if (*p == 0x0a) {
				outbuf[qty++] = '0';
				outbuf[qty++] = 'd';
			}
			p++;
			n--;
		}

		outbuf[qty] = 0;
		gdbstub_send_packet(outbuf);
	}
}