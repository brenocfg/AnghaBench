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

__attribute__((used)) static void usage (void)
{
	fprintf(stderr, "Usage: docproc {doc|depend} file\n");
	fprintf(stderr, "Input is read from file.tmpl. Output is sent to stdout\n");
	fprintf(stderr, "doc: frontend when generating kernel documentation\n");
	fprintf(stderr, "depend: generate list of files referenced within file\n");
	fprintf(stderr, "Environment variable SRCTREE: absolute path to sources.\n");
	fprintf(stderr, "                     KBUILD_SRC: absolute path to kernel source tree.\n");
}