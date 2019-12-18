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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const* const) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static
void
check_args(const int argc, const char *const argv[], const int required)
{
    if (argc < required) {
        fprintf(stderr, "Usage: %s helper-name [args]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
}