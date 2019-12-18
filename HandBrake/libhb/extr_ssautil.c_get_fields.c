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
 char** calloc (int,int) ; 
 char* get_field (char**) ; 
 char* strchr (char*,char) ; 
 char* strdup (char*) ; 

__attribute__((used)) static char ** get_fields(char * line, int last)
{
    int    count = 0, ii;
    char * pos;

    if (line == NULL || *line == 0)
    {
        return NULL;
    }

    // count number of fields
    count = 1;
    pos = line;
    while ((pos = strchr(pos, ',')) != NULL)
    {
        count++;
        pos++;
    }
    if (last > 0 && count > last)
    {
        count = last;
    }
    char ** result = calloc(count + 1, sizeof(char*));
    pos = line;
    for (ii = 0; ii < count - 1; ii++)
    {
        result[ii] = get_field(&pos);
    }
    result[ii] = strdup(pos);

    return result;
}