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
 int /*<<< orphan*/  error (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int warning_is_error ; 

__attribute__((used)) static void parse_warnings_arg(char *s) {
    if (!strcmp(s, "error"))
        warning_is_error = true;
    else if (strcmp(s, "all"))
        error("unknown -W option: %s", s);
}