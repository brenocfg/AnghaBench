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
 int NOPTS ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 scalar_t__ memcmp (unsigned char const*,char*,size_t) ; 
 unsigned char* optname ; 
 scalar_t__* optval ; 
 int /*<<< orphan*/  out1fmt (char*,...) ; 
 int /*<<< orphan*/  out1str (char*) ; 
 int /*<<< orphan*/  setoptionbyindex (int,int) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static void
minus_o(char *name, int val)
{
	int i;
	const unsigned char *on;
	size_t len;

	if (name == NULL) {
		if (val) {
			/* "Pretty" output. */
			out1str("Current option settings\n");
			for (i = 0, on = optname; i < NOPTS; i++, on += *on + 1)
				out1fmt("%-16.*s%s\n", *on, on + 1,
					optval[i] ? "on" : "off");
		} else {
			/* Output suitable for re-input to shell. */
			for (i = 0, on = optname; i < NOPTS; i++, on += *on + 1)
				out1fmt("%s %co %.*s%s",
				    i % 6 == 0 ? "set" : "",
				    optval[i] ? '-' : '+',
				    *on, on + 1,
				    i % 6 == 5 || i == NOPTS - 1 ? "\n" : "");
		}
	} else {
		len = strlen(name);
		for (i = 0, on = optname; i < NOPTS; i++, on += *on + 1)
			if (*on == len && memcmp(on + 1, name, len) == 0) {
				setoptionbyindex(i, val);
				return;
			}
		error("Illegal option -o %s", name);
	}
}