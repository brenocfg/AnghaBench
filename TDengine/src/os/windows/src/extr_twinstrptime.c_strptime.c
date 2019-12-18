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
struct tm {int tm_wday; int tm_mon; int tm_year; int tm_mday; int tm_hour; int tm_yday; int tm_min; int tm_sec; } ;

/* Variables and functions */
 int ALT_E ; 
 int ALT_O ; 
 int /*<<< orphan*/  LEGAL_ALT (int) ; 
 int /*<<< orphan*/  TM_YEAR_BASE ; 
 int /*<<< orphan*/ * abday ; 
 int /*<<< orphan*/ * abmon ; 
 int /*<<< orphan*/ * am_pm ; 
 int /*<<< orphan*/  conv_num (char const**,int*,int,int) ; 
 int /*<<< orphan*/ * day ; 
 scalar_t__ isspace (char const) ; 
 int /*<<< orphan*/ * mon ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char const*,size_t) ; 

char *
strptime(const char *buf, const char *fmt, struct tm *tm)
{
    char c;
    const char *bp;
    size_t len = 0;
    int alt_format, i, split_year = 0;

    bp = buf;

    while ((c = *fmt) != '\0') {
        /* Clear `alternate' modifier prior to new conversion. */
        alt_format = 0;

        /* Eat up white-space. */
        if (isspace(c)) {
            while (isspace(*bp))
                bp++;

            fmt++;
            continue;
        }

        if ((c = *fmt++) != '%')
            goto literal;


    again:		switch (c = *fmt++) {
    case '%':	/* "%%" is converted to "%". */
        literal :
            if (c != *bp++)
                return (0);
        break;

        /*
        * "Alternative" modifiers. Just set the appropriate flag
        * and start over again.
        */
    case 'E':	/* "%E?" alternative conversion modifier. */
        LEGAL_ALT(0);
        alt_format |= ALT_E;
        goto again;

    case 'O':	/* "%O?" alternative conversion modifier. */
        LEGAL_ALT(0);
        alt_format |= ALT_O;
        goto again;

        /*
        * "Complex" conversion rules, implemented through recursion.
        */
    case 'c':	/* Date and time, using the locale's format. */
        LEGAL_ALT(ALT_E);
        if (!(bp = strptime(bp, "%x %X", tm)))
            return (0);
        break;

    case 'D':	/* The date as "%m/%d/%y". */
        LEGAL_ALT(0);
        if (!(bp = strptime(bp, "%m/%d/%y", tm)))
            return (0);
        break;

    case 'R':	/* The time as "%H:%M". */
        LEGAL_ALT(0);
        if (!(bp = strptime(bp, "%H:%M", tm)))
            return (0);
        break;

    case 'r':	/* The time in 12-hour clock representation. */
        LEGAL_ALT(0);
        if (!(bp = strptime(bp, "%I:%M:%S %p", tm)))
            return (0);
        break;

    case 'T':	/* The time as "%H:%M:%S". */
        LEGAL_ALT(0);
        if (!(bp = strptime(bp, "%H:%M:%S", tm)))
            return (0);
        break;

    case 'X':	/* The time, using the locale's format. */
        LEGAL_ALT(ALT_E);
        if (!(bp = strptime(bp, "%H:%M:%S", tm)))
            return (0);
        break;

    case 'x':	/* The date, using the locale's format. */
        LEGAL_ALT(ALT_E);
        if (!(bp = strptime(bp, "%m/%d/%y", tm)))
            return (0);
        break;

        /*
        * "Elementary" conversion rules.
        */
    case 'A':	/* The day of week, using the locale's form. */
    case 'a':
        LEGAL_ALT(0);
        for (i = 0; i < 7; i++) {
            /* Full name. */
            len = strlen(day[i]);
            if (strncmp(day[i], bp, len) == 0)
                break;

            /* Abbreviated name. */
            len = strlen(abday[i]);
            if (strncmp(abday[i], bp, len) == 0)
                break;
        }

        /* Nothing matched. */
        if (i == 7)
            return (0);

        tm->tm_wday = i;
        bp += len;
        break;

    case 'B':	/* The month, using the locale's form. */
    case 'b':
    case 'h':
        LEGAL_ALT(0);
        for (i = 0; i < 12; i++) {
            /* Full name. */
            len = strlen(mon[i]);
            if (strncmp(mon[i], bp, len) == 0)
                break;

            /* Abbreviated name. */
            len = strlen(abmon[i]);
            if (strncmp(abmon[i], bp, len) == 0)
                break;
        }

        /* Nothing matched. */
        if (i == 12)
            return (0);

        tm->tm_mon = i;
        bp += len;
        break;

    case 'C':	/* The century number. */
        LEGAL_ALT(ALT_E);
        if (!(conv_num(&bp, &i, 0, 99)))
            return (0);

        if (split_year) {
            tm->tm_year = (tm->tm_year % 100) + (i * 100);
        }
        else {
            tm->tm_year = i * 100;
            split_year = 1;
        }
        break;

    case 'd':	/* The day of month. */
    case 'e':
        LEGAL_ALT(ALT_O);
        if (!(conv_num(&bp, &tm->tm_mday, 1, 31)))
            return (0);
        break;

    case 'k':	/* The hour (24-hour clock representation). */
        LEGAL_ALT(0);
        /* FALLTHROUGH */
    case 'H':
        LEGAL_ALT(ALT_O);
        if (!(conv_num(&bp, &tm->tm_hour, 0, 23)))
            return (0);
        break;

    case 'l':	/* The hour (12-hour clock representation). */
        LEGAL_ALT(0);
        /* FALLTHROUGH */
    case 'I':
        LEGAL_ALT(ALT_O);
        if (!(conv_num(&bp, &tm->tm_hour, 1, 12)))
            return (0);
        if (tm->tm_hour == 12)
            tm->tm_hour = 0;
        break;

    case 'j':	/* The day of year. */
        LEGAL_ALT(0);
        if (!(conv_num(&bp, &i, 1, 366)))
            return (0);
        tm->tm_yday = i - 1;
        break;

    case 'M':	/* The minute. */
        LEGAL_ALT(ALT_O);
        if (!(conv_num(&bp, &tm->tm_min, 0, 59)))
            return (0);
        break;

    case 'm':	/* The month. */
        LEGAL_ALT(ALT_O);
        if (!(conv_num(&bp, &i, 1, 12)))
            return (0);
        tm->tm_mon = i - 1;
        break;

    case 'p':	/* The locale's equivalent of AM/PM. */
        LEGAL_ALT(0);
        /* AM? */
        if (strcmp(am_pm[0], bp) == 0) {
            if (tm->tm_hour > 11)
                return (0);

            bp += strlen(am_pm[0]);
            break;
        }
        /* PM? */
        else if (strcmp(am_pm[1], bp) == 0) {
            if (tm->tm_hour > 11)
                return (0);

            tm->tm_hour += 12;
            bp += strlen(am_pm[1]);
            break;
        }

        /* Nothing matched. */
        return (0);

    case 'S':	/* The seconds. */
        LEGAL_ALT(ALT_O);
        if (!(conv_num(&bp, &tm->tm_sec, 0, 61)))
            return (0);
        break;

    case 'U':	/* The week of year, beginning on sunday. */
    case 'W':	/* The week of year, beginning on monday. */
        LEGAL_ALT(ALT_O);
        /*
        * XXX This is bogus, as we can not assume any valid
        * information present in the tm structure at this
        * point to calculate a real value, so just check the
        * range for now.
        */
        if (!(conv_num(&bp, &i, 0, 53)))
            return (0);
        break;

    case 'w':	/* The day of week, beginning on sunday. */
        LEGAL_ALT(ALT_O);
        if (!(conv_num(&bp, &tm->tm_wday, 0, 6)))
            return (0);
        break;

    case 'Y':	/* The year. */
        LEGAL_ALT(ALT_E);
        if (!(conv_num(&bp, &i, 0, 9999)))
            return (0);

        tm->tm_year = i - TM_YEAR_BASE;
        break;

    case 'y':	/* The year within 100 years of the epoch. */
        LEGAL_ALT(ALT_E | ALT_O);
        if (!(conv_num(&bp, &i, 0, 99)))
            return (0);

        if (split_year) {
            tm->tm_year = ((tm->tm_year / 100) * 100) + i;
            break;
        }
        split_year = 1;
        if (i <= 68)
            tm->tm_year = i + 2000 - TM_YEAR_BASE;
        else
            tm->tm_year = i + 1900 - TM_YEAR_BASE;
        break;

        /*
        * Miscellaneous conversions.
        */
    case 'n':	/* Any kind of white-space. */
    case 't':
        LEGAL_ALT(0);
        while (isspace(*bp))
            bp++;
        break;


    default:	/* Unknown/unsupported conversion. */
        return (0);
    }


    }

    /* LINTED functional specification */
    return ((char *)bp);
}