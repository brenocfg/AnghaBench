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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

void usage(void)
{
	fprintf(stderr, "Usage:\n");
	fprintf(stderr, "\twol -i monitor_dev -m DE:VI:CE:MA:CW:OL -n #num -v\n");

	fprintf(stderr, "\nDescription:\n");
	fprintf(stderr, "\tThis utility generates a WOL packet for the"
			"given [MAC] address and tries to injects"
			"it into [monitor_dev]\n");

	exit(EXIT_FAILURE);
}