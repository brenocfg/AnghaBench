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
 int ERR ; 
 char* errmsg ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 scalar_t__ seek_write ; 
 char* sfn ; 
 int /*<<< orphan*/ * sfp ; 
 scalar_t__ sfseek ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (char*) ; 

int
close_sbuf(void)
{
	if (sfp) {
		if (fclose(sfp) < 0) {
			fprintf(stderr, "%s: %s\n", sfn, strerror(errno));
			errmsg = "cannot close temp file";
			return ERR;
		}
		sfp = NULL;
		unlink(sfn);
	}
	sfseek = seek_write = 0;
	return 0;
}