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
 int /*<<< orphan*/  ATF_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATF_CHECK_STREQ_MSG (char const*,char*,char*,char*,char const*) ; 
 char* atf_utils_readline (int) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static
void
check_line(int fd, const char *exp)
{
    char *line = atf_utils_readline(fd);
    ATF_CHECK(line != NULL);
    ATF_CHECK_STREQ_MSG(exp, line, "read: '%s', expected: '%s'", line, exp);
    free(line);
}