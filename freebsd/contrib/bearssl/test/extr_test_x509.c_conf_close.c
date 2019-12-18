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
 int /*<<< orphan*/  SB_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * conf ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * line_builder ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
conf_close(void)
{
	if (conf != NULL) {
		if (ferror(conf)) {
			fprintf(stderr, "read error on configuration file\n");
			exit(EXIT_FAILURE);
		}
		fclose(conf);
		conf = NULL;
	}
	if (line_builder != NULL) {
		SB_free(line_builder);
		line_builder = NULL;
	}
}