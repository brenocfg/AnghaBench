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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*,...) ; 

__attribute__((used)) static void print_string_list(FILE *out, const char* const *list, const char *prefix)
{
    if (out != NULL && prefix != NULL)
    {
        if (list != NULL)
        {
            while (*list != NULL)
            {
                fprintf(out, "%s%s\n", prefix, *list++);
            }
        }
        else
        {
            fprintf(out, "%s" "Option not supported by encoder\n", prefix);
        }
    }
}