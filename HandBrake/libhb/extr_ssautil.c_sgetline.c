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
 char* hb_strndup (char*,int) ; 
 char* strchr (char*,char) ; 
 char* strdup (char*) ; 

__attribute__((used)) static char * sgetline(char * str)
{
    char * eol;

    if (str == NULL)
    {
        return NULL;
    }

    // find end of line
    eol = strchr(str, '\n');
    if (eol != NULL)
    {
        if (eol > str && *(eol - 1) == '\r')
        {
            eol--;
        }
    }
    if (eol != NULL)
    {
        return hb_strndup(str, eol - str);
    }
    else
    {
        return strdup(str);
    }
}