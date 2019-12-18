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
 char* my_strndup (char const*,int) ; 
 char* reverse_search_char (char const*,char const*,char) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char** str_width_split( const char *str, int width )
{
    const char *  pos;
    const char *  end;
    char ** ret;
    int     count, ii;
    int     len;
    char    delem = ' ';

    if ( str == NULL || str[0] == 0 )
    {
        ret = malloc( sizeof(char*) );
        if ( ret == NULL ) return ret;
        *ret = NULL;
        return ret;
    }

    len = strlen(str);

    // Find number of elements in the string
    count = 1;
    pos = str;
    end = pos + width;
    while (end < str + len)
    {
        end = reverse_search_char(pos, end, delem);
        if (end == pos)
        {
            // Shouldn't happen for reasonable input
            break;
        }
        count++;
        pos = end + 1;
        end = pos + width;
    }
    count++;
    ret = calloc( ( count + 1 ), sizeof(char*) );
    if ( ret == NULL ) return ret;

    pos = str;
    end = pos + width;
    for (ii = 0; ii < count - 1 && end < str + len; ii++)
    {
        end = reverse_search_char(pos, end, delem);
        if (end == pos)
        {
            break;
        }
        ret[ii] = my_strndup(pos, end - pos);
        pos = end + 1;
        end = pos + width;
    }
    if (*pos != 0 && ii < count - 1)
    {
        ret[ii] = my_strndup(pos, width);
    }

    return ret;
}