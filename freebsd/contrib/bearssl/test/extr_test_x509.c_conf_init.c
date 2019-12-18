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
 int /*<<< orphan*/  SB_new () ; 
 int /*<<< orphan*/ * conf ; 
 int conf_delayed_char ; 
 int conf_linenum ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  line_builder ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
conf_init(const char *fname)
{
	conf = fopen(fname, "r");
	if (conf == NULL) {
		fprintf(stderr, "could not open file '%s'\n", fname);
		exit(EXIT_FAILURE);
	}
	conf_delayed_char = -1;
	conf_linenum = 1;
	line_builder = SB_new();
}