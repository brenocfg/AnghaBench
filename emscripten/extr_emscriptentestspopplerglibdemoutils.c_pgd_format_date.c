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
typedef  scalar_t__ time_t ;
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  s ;
typedef  int /*<<< orphan*/  gchar ;

/* Variables and functions */
 int /*<<< orphan*/ * g_locale_to_utf8 (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct tm* localtime (scalar_t__*) ; 
 size_t strftime (char*,int,char const*,struct tm*) ; 

gchar *
pgd_format_date (time_t utime)
{
	time_t time = (time_t) utime;
	char s[256];
	const char *fmt_hack = "%c";
	size_t len;
#ifdef HAVE_LOCALTIME_R
	struct tm t;
	if (time == 0 || !localtime_r (&time, &t)) return NULL;
	len = strftime (s, sizeof (s), fmt_hack, &t);
#else
	struct tm *t;
	if (time == 0 || !(t = localtime (&time)) ) return NULL;
	len = strftime (s, sizeof (s), fmt_hack, t);
#endif

	if (len == 0 || s[0] == '\0') return NULL;

	return g_locale_to_utf8 (s, -1, NULL, NULL, NULL);
}