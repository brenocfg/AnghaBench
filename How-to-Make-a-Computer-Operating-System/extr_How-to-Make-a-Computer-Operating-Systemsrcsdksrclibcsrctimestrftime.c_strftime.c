#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t tm_wday; size_t tm_mon; int tm_year; int tm_mday; int tm_hour; int tm_min; int tm_sec; int /*<<< orphan*/  tm_yday; } ;
typedef  TYPE_1__ tm_t ;

/* Variables and functions */
 int /*<<< orphan*/  APPEND (char*) ; 
 int STRFT_ALTFORM ; 
 char** day_names ; 
 int mktime (TYPE_1__*) ; 
 char** month_names ; 
 char** sday_names ; 
 char** smonth_names ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int) ; 

size_t strftime(char* s, size_t max, const char* format,
                const tm_t* tm){
    size_t ret = 0;
    int state;
    int flags; 
    char tmp[max];

    s[0] = '\0'; /* Initialize s */
    max--; /* Reserve space for '\0' at the end */
    state = flags = 0;

    for( ; *format != '\0'; format++){
        switch(state){
            case 0:
                if(*format != '%'){
                    if(ret < max){
                        s[ret++] = *format;
                        s[ret] = '\0';
                    } else {
                        s[ret] = '\0';
                        return 0;
                    }
                    break;
                }
                state++;
                format++;
            case 1:
                if(*format == '%'){
                    if(ret < max){
                        s[ret++] = '%';
                        s[ret] = '\0';
                    } else {
                        s[ret] = '\0';
                        return 0;
                    }
                    state = flags = 0;
                    break;
                }
                /* TODO: locale-independent, we need locales first :)
                if(*format == 'E'){
                } */
                if(*format == 'O'){
                    flags |= STRFT_ALTFORM;
                    /* TODO: use this */
                }
                /* TODO: glibc modifiers: _-0^# */
                state++;
            case 2:
                switch(*format){
                    case 'a':
                        APPEND(sday_names[tm->tm_wday]);
                        break;
                    case 'A':
                        APPEND(day_names[tm->tm_wday]);
                        break;
                    case 'h':
                    case 'b':
                        APPEND(smonth_names[tm->tm_mon]);
                        break;
                    case 'B':
                        APPEND(month_names[tm->tm_mon]);
                        break;
                    case 'c':
                        /* The preferred date and time representation for the current locale. */
                        strftime(tmp, max-ret, "%a %b %e %H:%M:%S %Z %Y", tm);
                        APPEND(tmp);
                        break;
                    case 'C':
                        snprintf(tmp, max, "%d", tm->tm_year / 100);
                        APPEND(tmp);
                        break;
                    case 'd':
                        snprintf(tmp, max, "%02d", tm->tm_mday);
                        APPEND(tmp);
                        break;
                    case 'D':
                        strftime(tmp, max-ret, "%m/%d/%y", tm);
                        APPEND(tmp);
                        break;
                    case 'e':
                        snprintf(tmp, max, "%2d", tm->tm_mday);
                        APPEND(tmp);
                        break;
                    case 'F':
                        strftime(tmp, max-ret, "%Y-%m-%d", tm);
                        APPEND(tmp);
                        break;
                    case 'G':
/* The ISO 8601 year with century as a decimal number.  The 4-digit year corresponding to the ISO  week  number
   (see  %V).  This has the same format and value as %y, except that if the ISO week number belongs to the
   previous or next year, that year is used instead. (TZ)*/
                        break;
                    case 'g':
                        /* Like %G, but without century, that is, with a 2-digit year (00-99). (TZ) */
                        break;
                    case 'H':
                        snprintf(tmp, max, "%02d", tm->tm_hour);
                        APPEND(tmp);
                        break;
                    case 'I':
                        snprintf(tmp, max, "%02d", tm->tm_hour % 12);
                        APPEND(tmp);
                        break;
                    case 'j':
                        /* Day of the year, 001-366 */
                        snprintf(tmp, max, "%03d", tm->tm_yday + 1);
                        APPEND(tmp);
                        break;
                    case 'k':
                        snprintf(tmp, max, "%2d", tm->tm_hour);
                        APPEND(tmp);
                        break;
                    case 'l':
                        snprintf(tmp, max, "%2d", tm->tm_hour % 12);
                        APPEND(tmp);
                        break;
                    case 'm':
                        snprintf(tmp, max, "%02d", tm->tm_mon + 1);
                        APPEND(tmp);
                        break;
                    case 'M':
                        snprintf(tmp, max, "%02d", tm->tm_min);
                        APPEND(tmp);
                        break;
                    case 'n':
                        APPEND("\n");
                        break;
                    case 'p':
                        if(tm->tm_hour >= 12){
                            APPEND("PM");
                        }else{
                            APPEND("AM");
                        }
                        break;
                    case 'P':
                        if(tm->tm_hour >= 12){
                            APPEND("pm");
                        }else{
                            APPEND("am");
                        }
                        break;
                    case 'r':
                        strftime(tmp, max-ret, "%I:%M:%S %p", tm);
                        APPEND(tmp);
                        break;
                    case 'R':
                        strftime(tmp, max-ret, "%H:%M", tm);
                        APPEND(tmp);
                        break;
                    case 's':
                        snprintf(tmp, max, "%llu", mktime((tm_t*) tm));
                        APPEND(tmp);
                        break;
                    case 'S':
                        snprintf(tmp, max, "%02d", tm->tm_sec);
                        APPEND(tmp);
                        break;
                    case 't':
                        APPEND("\t");
                        break;
                    case 'T':
                        strftime(tmp, max-ret, "%H:%M:%S", tm);
                        APPEND(tmp);
                        break;
                    case 'u':
                        /* Day of the week, 1-7, Monday=1 */
                        snprintf(tmp, max, "%d", 1 + (tm->tm_wday + 6 ) % 7);
                        APPEND(tmp);
                        break;
                    case 'U':
/* The week number of the current year as a decimal number, range 00 to 53, starting with the first  Sunday  as
   the first day of week 01.*/
                        break;
                    case 'V':
/*  The  ISO  8601:1988 week number of the current year as a decimal number, range 01 to 53, where week 1 is the
    first week that has at least 4 days in the current year, and with Monday as the first day of the week.   See
    also %U and %W. */
                        break;
                    case 'w':
                        /* Day of the week, 0-6, Sunday=0 */
                        snprintf(tmp, max, "%d", tm->tm_wday);
                        APPEND(tmp);
                        break;
                    case 'W':
/* The  week  number of the current year as a decimal number, range 00 to 53, starting with the first Monday as
   the first day of week 01. */
                        break;
                    case 'x':
                        /* The preferred date representation for the current locale without the time. */
                        strftime(tmp, max-ret, "%a %b %e %Z %Y", tm);
                        APPEND(tmp);
                        break;
                    case 'X':
                        /* The preferred time representation for the current locale without the date. */
                        strftime(tmp, max-ret, "%H:%M:%S", tm);
                        APPEND(tmp);
                        break;
                    case 'y':
                        /* The year as a decimal number without a century (range 00 to 99). */
                        snprintf(tmp, max, "%02d", tm->tm_year % 100);
                        APPEND(tmp);
                        break;
                    case 'Y':
                        /* The year as a decimal number including the century. */
                        snprintf(tmp, max, "%d", tm->tm_year);
                        APPEND(tmp);
                        break;
                    case 'z':
/* The  time-zone  as  hour  offset   from   GMT.    Required   to   emit   RFC 822-conformant   dates   (using
   "%a, %d %b %Y %H:%M:%S %z"). (GNU) */
                        break;
                    case 'Z':
                        /* The time zone or name or abbreviation. */
                        break;
                    default:
                        break;
                }
            state = flags = 0;
        }
    }

    s[ret] = '\0';

    return ret;
}