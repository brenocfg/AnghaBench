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
typedef  int /*<<< orphan*/  regex_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  REG_EXTENDED ; 
 int REG_NOMATCH ; 
 int /*<<< orphan*/  printf (char*,char const*,char const*) ; 
 scalar_t__ regcomp (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int regexec (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
bool
grep_string(const char *regex, const char *str)
{
    int res;
    regex_t preg;

    printf("Looking for '%s' in '%s'\n", regex, str);
    ATF_REQUIRE(regcomp(&preg, regex, REG_EXTENDED) == 0);

    res = regexec(&preg, str, 0, NULL, 0);
    ATF_REQUIRE(res == 0 || res == REG_NOMATCH);

    regfree(&preg);

    return res == 0;
}