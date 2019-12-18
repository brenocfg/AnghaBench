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
 int /*<<< orphan*/  out1 ; 
 int /*<<< orphan*/  out1fmt (char*,int) ; 
 int /*<<< orphan*/  outbin (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 

int
wordexpcmd(int argc, char **argv)
{
	size_t len;
	int i;

	out1fmt("%08x", argc - 1);
	for (i = 1, len = 0; i < argc; i++)
		len += strlen(argv[i]);
	out1fmt("%08x", (int)len);
	for (i = 1; i < argc; i++)
		outbin(argv[i], strlen(argv[i]) + 1, out1);
        return (0);
}