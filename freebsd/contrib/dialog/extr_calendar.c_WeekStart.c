#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* week_start; } ;

/* Variables and functions */
 int MAX_DAYS ; 
 int /*<<< orphan*/  _NL_TIME_FIRST_WEEKDAY ; 
 int /*<<< orphan*/  _NL_TIME_WEEK_1STDAY ; 
 TYPE_1__ dialog_vars ; 
 int /*<<< orphan*/  nameOfDayOfWeek (int) ; 
 int* nl_langinfo (int /*<<< orphan*/ ) ; 
 int read_locale_setting (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,size_t) ; 
 long strtol (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
WeekStart(void)
{
    int result = 0;
    char *option = dialog_vars.week_start;
    if (option != 0) {
	if (option[0]) {
	    char *next = 0;
	    long check = strtol(option, &next, 0);
	    if (next == 0 ||
		next == option ||
		*next != '\0') {
		if (!strcmp(option, "locale")) {
#if defined(ENABLE_NLS) && defined(HAVE_NL_LANGINFO_1STDAY)
		    /*
		     * glibc-specific.
		     */
		    int first_day = nl_langinfo(_NL_TIME_FIRST_WEEKDAY)[0];
		    char *basis_ptr = nl_langinfo(_NL_TIME_WEEK_1STDAY);
		    int basis_day = (int) (intptr_t) basis_ptr;
#elif defined(HAVE_DLG_GAUGE)
		    /*
		     * probably Linux-specific, but harmless otherwise.  When
		     * available, the locale program will return a single
		     * integer on one line.
		     */
		    int first_day = read_locale_setting("first_weekday", 0);
		    int basis_day = read_locale_setting("week-1stday", 0);
#endif
#if (defined(ENABLE_NLS) && defined(HAVE_NL_LANGINFO_1STDAY)) || defined(HAVE_DLG_GAUGE)
		    int week_1stday = -1;
		    if (basis_day == 19971130)
			week_1stday = 0;	/* Sun */
		    else if (basis_day == 19971201)
			week_1stday = 1;	/* Mon */
		    if (week_1stday >= 0) {
			result = first_day - week_1stday - 1;
		    }
#else
		    result = 0;	/* Sun */
#endif
		} else {
		    int day;
		    size_t eql = strlen(option);
		    for (day = 0; day < MAX_DAYS; ++day) {
			if (!strncmp(nameOfDayOfWeek(day), option, eql)) {
			    result = day;
			    break;
			}
		    }
		}
	    } else if (check < 0) {
		result = -1;
	    } else {
		result = (int) (check % MAX_DAYS);
	    }
	}
    }
    return result;
}