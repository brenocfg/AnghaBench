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
struct tty_struct {struct r3964_info* disc_data; } ;
struct r3964_info {int dummy; } ;

/* Variables and functions */
 char TTY_NORMAL ; 
 int /*<<< orphan*/  receive_char (struct r3964_info*,unsigned char const) ; 
 int /*<<< orphan*/  receive_error (struct r3964_info*,char) ; 

__attribute__((used)) static void r3964_receive_buf(struct tty_struct *tty, const unsigned char *cp,
			char *fp, int count)
{
	struct r3964_info *pInfo = tty->disc_data;
	const unsigned char *p;
	char *f, flags = 0;
	int i;

	for (i = count, p = cp, f = fp; i; i--, p++) {
		if (f)
			flags = *f++;
		if (flags == TTY_NORMAL) {
			receive_char(pInfo, *p);
		} else {
			receive_error(pInfo, flags);
		}

	}
}