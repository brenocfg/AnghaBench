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

/* Variables and functions */
 int /*<<< orphan*/  out1c (char) ; 
 int /*<<< orphan*/  out1fmt (char*,int) ; 
 int /*<<< orphan*/  out1str (char*) ; 
 scalar_t__ strlen (int) ; 
 int sys_nsig ; 
 int* sys_signame ; 

__attribute__((used)) static void
printsignals(void)
{
	int n, outlen;

	outlen = 0;
	for (n = 1; n < sys_nsig; n++) {
		if (sys_signame[n]) {
			out1fmt("%s", sys_signame[n]);
			outlen += strlen(sys_signame[n]);
		} else {
			out1fmt("%d", n);
			outlen += 3;	/* good enough */
		}
		++outlen;
		if (outlen > 71 || n == sys_nsig - 1) {
			out1str("\n");
			outlen = 0;
		} else {
			out1c(' ');
		}
	}
}