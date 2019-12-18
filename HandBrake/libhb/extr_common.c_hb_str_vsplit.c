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
 char** malloc (int) ; 
 char* strchr_quote (char const*,char,char) ; 
 int strlen (char const*) ; 
 char* strndup_quote (char const*,char,int) ; 

char** hb_str_vsplit( const char *str, char delem )
{
    const char *  pos;
    const char *  end;
    char       ** ret;
    int           count, i;
    char          quote = '"';

    if (delem == '"')
    {
        quote = '\'';
    }
    if ( str == NULL || str[0] == 0 )
    {
        ret = malloc( sizeof(char*) );
        if ( ret == NULL ) return ret;
        *ret = NULL;
        return ret;
    }

    // Find number of elements in the string
    count = 1;
    pos = str;
    while ( ( pos = strchr_quote( pos, delem, quote ) ) != NULL )
    {
        count++;
        pos++;
    }

    ret = calloc( ( count + 1 ), sizeof(char*) );
    if ( ret == NULL ) return ret;

    pos = str;
    for ( i = 0; i < count - 1; i++ )
    {
        end = strchr_quote( pos, delem, quote );
        ret[i] = strndup_quote(pos, quote, end - pos);
        pos = end + 1;
    }
    ret[i] = strndup_quote(pos, quote, strlen(pos));

    return ret;
}