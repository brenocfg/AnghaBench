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
struct dtc_file {struct dtc_file* dir; int /*<<< orphan*/  name; int /*<<< orphan*/  file; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct dtc_file*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void dtc_close_file(struct dtc_file *file)
{
	if (fclose(file->file))
		die("Error closing \"%s\": %s\n", file->name, strerror(errno));

	free(file->dir);
	free(file);
}