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
 scalar_t__ MAX (scalar_t__,size_t) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  strncat (char*,char const*,size_t) ; 

char * hb_strncat_dup( const char * s1, const char * s2, size_t n )
{
    size_t len;
    char * str;

    len = 0;
    if( s1 )
        len += strlen( s1 );
    if( s2 )
        len += MAX( strlen( s2 ), n );
    if( !len )
        return NULL;

    str = malloc( len + 1 );
    if( !str )
        return NULL;

    if( s1 )
        strcpy( str, s1 );
    else
        strcpy( str, "" );

    if (s2)
    {
        strncat( str, s2, n );
    }

    return str;
}