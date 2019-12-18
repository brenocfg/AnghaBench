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
struct hvsi_struct {int sysrq; int /*<<< orphan*/  tty; } ;

/* Variables and functions */
 int /*<<< orphan*/  handle_sysrq (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_insert_flip_char (int /*<<< orphan*/ ,char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hvsi_insert_chars(struct hvsi_struct *hp, const char *buf, int len)
{
	int i;

	for (i=0; i < len; i++) {
		char c = buf[i];
#ifdef CONFIG_MAGIC_SYSRQ
		if (c == '\0') {
			hp->sysrq = 1;
			continue;
		} else if (hp->sysrq) {
			handle_sysrq(c, hp->tty);
			hp->sysrq = 0;
			continue;
		}
#endif /* CONFIG_MAGIC_SYSRQ */
		tty_insert_flip_char(hp->tty, c, 0);
	}
}