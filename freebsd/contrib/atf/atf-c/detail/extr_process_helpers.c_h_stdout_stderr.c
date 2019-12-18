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
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static
int
h_stdout_stderr(const char *id)
{
    fprintf(stdout, "Line 1 to stdout for %s\n", id);
    fprintf(stdout, "Line 2 to stdout for %s\n", id);
    fprintf(stderr, "Line 1 to stderr for %s\n", id);
    fprintf(stderr, "Line 2 to stderr for %s\n", id);

    return EXIT_SUCCESS;
}