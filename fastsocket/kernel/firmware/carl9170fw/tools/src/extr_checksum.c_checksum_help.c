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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void checksum_help(void)
{
	fprintf(stderr, "Usage:\n");
	fprintf(stderr, "\tchecksum FW-FILE\n");

	fprintf(stderr, "\nDescription:\n");
	fprintf(stderr, "\tThis simple utility adds/updates various "
			"checksums.\n");

	fprintf(stderr, "\nParameteres:\n");
	fprintf(stderr, "\t 'FW-FILE'	= firmware name\n");
	fprintf(stderr, "\n");
}