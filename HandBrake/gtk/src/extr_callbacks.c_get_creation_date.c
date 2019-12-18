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
struct tm {int dummy; } ;
struct stat {int /*<<< orphan*/  st_mtime; } ;

/* Variables and functions */
 scalar_t__ g_stat (char const*,struct stat*) ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 scalar_t__ parse_datestring (char const*,struct tm*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strftime (char*,int,char const*,struct tm*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char*
get_creation_date(const char *pattern, const char *metaValue, const char *file)
{
    char date[11] = "";
    if (metaValue != NULL && strlen(metaValue) > 1)
    {
        struct tm tm;
        if (parse_datestring(metaValue, &tm))
        {
            strftime(date, 11, pattern, &tm);
        }
    }
    else
    {
        struct stat stbuf;
        if (g_stat(file, &stbuf) == 0){
            struct tm *tm;
            tm = localtime(&(stbuf.st_mtime));
            strftime(date, 11, pattern, tm);
        }
    }
    return strdup(date);
}