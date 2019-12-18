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
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 

__attribute__((used)) static int field_index(char ** fields, char * name)
{
    int ii;

    if (fields == NULL || name == NULL)
    {
        return -1;
    }
    for (ii = 0; fields[ii] != NULL; ii++)
    {
        if (!strcasecmp(name, fields[ii]))
        {
            return ii;
        }
    }
    return -1;
}