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
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  time_t ;
struct tm {int tm_hour; int tm_min; int tm_sec; } ;
typedef  scalar_t__ hb_debug_level_t ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int /*<<< orphan*/  GetConsoleOutputCP () ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int) ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ global_verbosity_level ; 
 char* hb_strdup_vaprintf (char*,int /*<<< orphan*/ ) ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int,char const*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

void hb_valog( hb_debug_level_t level, const char * prefix, const char * log, va_list args)
{
    char      * string;
    time_t      _now;
    struct tm * now;
    char        preamble[362];

    if( global_verbosity_level < level )
    {
        /* Hiding message */
        return;
    }

    /* Get the time */
    _now = time( NULL );
    now  = localtime( &_now );
    if ( prefix && *prefix )
    {
        // limit the prefix length
        snprintf( preamble, 361, "[%02d:%02d:%02d] %s %s\n",
                 now->tm_hour, now->tm_min, now->tm_sec, prefix, log );
    }
    else
    {
        snprintf( preamble, 361, "[%02d:%02d:%02d] %s\n",
                  now->tm_hour, now->tm_min, now->tm_sec, log );
    }

    string = hb_strdup_vaprintf(preamble, args);

#ifdef SYS_MINGW
    wchar_t     *wstring; /* 360 chars + \n + \0 */
    int          len;

    len = strlen(string) + 1;
    wstring = malloc(2 * len);

    // Convert internal utf8 to "console output code page".
    //
    // This is just bizarre windows behavior.  You would expect that
    // printf would automatically convert a wide character string to
    // the current "console output code page" when using the "%ls" format
    // specifier.  But it doesn't... so we must do it.
    if (!MultiByteToWideChar(CP_UTF8, 0, string, -1, wstring, len))
    {
        free(string);
        free(wstring);
        return;
    }
    free(string);
    string = malloc(2 * len);
    if (!WideCharToMultiByte(GetConsoleOutputCP(), 0, wstring, -1, string, len,
                             NULL, NULL))
    {
        free(string);
        free(wstring);
        return;
    }
    free(wstring);
#endif

    /* Print it */
    fprintf( stderr, "%s", string );
    free(string);
}