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

__attribute__((used)) static void
printFormat(void)
{
    fprintf(stderr, 
        "The copyright string should be contained in the NSHumanReadableCopyright key.\n"
        "It should be of the format:\n"
        "\tCopyright © [year(s) of publication] Apple Inc. All rights reserved.\n\n"
        "where [year(s) of publication] is a comma-separated list of years and/or\n"
        "year ranges, e.g., 2004, 2006-2008.  Years must be four digits.  Year ranges\n"
        "may not contain spaces and must use four digits for both years.\n\n"
        "The following are examples of valid copyright strings:\n"
        "\tCopyright © 2008 Apple Inc. All rights reserved.\n"
        "\tCopyright © 2004-2008 Apple Inc. All rights reserved.\n"
        "\tCopyright © 1998,2000-2002,2004,2006-2008 Apple Inc. All rights reserved.\n");
}