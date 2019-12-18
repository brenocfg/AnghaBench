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
 int REG_EXTENDED ; 
 int REG_ICASE ; 
 int /*<<< orphan*/  hb_log (char*,char const*) ; 
 scalar_t__ regcomp (int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ regexec (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regfree (int /*<<< orphan*/ *) ; 

int hb_validate_param_string(const char *regex_pattern, const char *param_string)
{
    regex_t regex_temp;

    if (regcomp(&regex_temp, regex_pattern, REG_EXTENDED|REG_ICASE) == 0)
    {
        if (regexec(&regex_temp, param_string, 0, NULL, 0) == 0)
        {
            regfree(&regex_temp);
            return 0;
        }
    }
    else
    {
        hb_log("hb_validate_param_string: Error compiling regex for pattern (%s).\n", param_string);
    }

    regfree(&regex_temp);
    return 1;
}