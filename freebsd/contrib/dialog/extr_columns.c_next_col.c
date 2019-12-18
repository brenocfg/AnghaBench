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
 char* column_separator () ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static char *
next_col(char *source, unsigned offset)
{
    char *mark = column_separator();
    char *result = source + offset;
    if (offset)
	result += strlen(mark);
    return strstr(result, mark);
}