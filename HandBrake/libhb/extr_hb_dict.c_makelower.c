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
 char* malloc (int) ; 
 int strlen (char const*) ; 
 char tolower (char const) ; 

__attribute__((used)) static char * makelower(const char *key)
{
    int    ii, len = strlen(key);
    char * lower = malloc(len + 1);

    for (ii = 0; ii < len; ii++)
    {
        lower[ii] = tolower(key[ii]);
    }
    lower[ii] = '\0';
    return lower;
}