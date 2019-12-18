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
 int GetTempPath (int,char*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * getcwd (char*,int) ; 
 char* getenv (char*) ; 
 scalar_t__ getpid () ; 
 char* hb_strdup_printf (char*,char*,int) ; 
 char* malloc (int) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 

char * hb_get_temporary_directory()
{
    char * path, * base, * p;

    /* Create the base */
#if defined( SYS_CYGWIN ) || defined( SYS_MINGW )
    base = malloc(MAX_PATH);
    int i_size = GetTempPath( MAX_PATH, base );
    if( i_size <= 0 || i_size >= MAX_PATH )
    {
        if( getcwd( base, MAX_PATH ) == NULL )
            strcpy( base, "c:" ); /* Bad fallback but ... */
    }

    /* c:/path/ works like a charm under cygwin(win32?) so use it */
    while( ( p = strchr( base, '\\' ) ) )
        *p = '/';
#else
    if( (p = getenv( "TMPDIR" ) ) != NULL ||
        (p = getenv( "TEMP" ) )   != NULL )
        base = strdup(p);
    else
        base = strdup("/tmp");
#endif
    /* I prefer to remove evntual last '/' (for cygwin) */
    if( base[strlen(base)-1] == '/' )
        base[strlen(base)-1] = '\0';

    path = hb_strdup_printf("%s/hb.%d", base, (int)getpid());
    free(base);

    return path;
}