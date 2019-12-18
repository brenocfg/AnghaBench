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
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/ * pt_header ; 
 scalar_t__ pt_shown ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
finish_progress(char *done)
{
	if (pt_shown) {
		(void) printf("%s\n", done);
		(void) fflush(stdout);
	}
	free(pt_header);
	pt_header = NULL;
}