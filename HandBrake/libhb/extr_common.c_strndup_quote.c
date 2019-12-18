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

__attribute__((used)) static char *strndup_quote(const char *str, char q, int len)
{
    if (str == NULL)
        return NULL;

    char * res;
    int str_len = strlen( str );
    int src = 0, dst = 0;
    res = malloc( len > str_len ? str_len + 1 : len + 1 );
    if ( res == NULL ) return res;

    while (str[src] != 0 && src < len)
    {
        if (str[src] == q)
            src++;
        else
            res[dst++] = str[src++];
    }
    res[dst] = '\0';
    return res;
}