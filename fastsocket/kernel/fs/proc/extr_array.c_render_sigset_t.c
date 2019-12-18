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
struct seq_file {int dummy; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int _NSIG ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 scalar_t__ sigismember (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void render_sigset_t(struct seq_file *m, const char *header,
				sigset_t *set)
{
	int i;

	seq_printf(m, "%s", header);

	i = _NSIG;
	do {
		int x = 0;

		i -= 4;
		if (sigismember(set, i+1)) x |= 1;
		if (sigismember(set, i+2)) x |= 2;
		if (sigismember(set, i+3)) x |= 4;
		if (sigismember(set, i+4)) x |= 8;
		seq_printf(m, "%x", x);
	} while (i >= 4);

	seq_printf(m, "\n");
}