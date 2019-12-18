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
 int MAX_LEN ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int
widest_line(char **list)
{
    int result = MAX_LEN;
    char *value;

    if (list != 0) {
	while ((value = *list++) != 0) {
	    int check = (int) strlen(value);
	    if (check > result)
		result = check;
	}
    }
    return result;
}