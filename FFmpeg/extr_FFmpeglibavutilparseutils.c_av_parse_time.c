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
typedef  int time_t ;
struct tm {int tm_hour; int tm_min; int tm_sec; int tm_isdst; int /*<<< orphan*/  member_0; } ;
typedef  int int64_t ;

/* Variables and functions */
 int AVERROR (scalar_t__) ; 
 scalar_t__ EINVAL ; 
 scalar_t__ ERANGE ; 
 int FF_ARRAY_ELEMS (char const* const*) ; 
 int INT64_MAX ; 
 int INT64_MIN ; 
 int av_gettime () ; 
 scalar_t__ av_isdigit (char const) ; 
 scalar_t__ av_isspace (char const) ; 
 char* av_small_strptime (char const*,char const* const,struct tm*) ; 
 int /*<<< orphan*/  av_strcasecmp (char const*,char*) ; 
 int av_timegm (struct tm*) ; 
 scalar_t__ errno ; 
 struct tm* gmtime_r (int*,struct tm*) ; 
 struct tm* localtime_r (int*,struct tm*) ; 
 int mktime (struct tm*) ; 
 int strtoll (char const*,char**,int) ; 

int av_parse_time(int64_t *timeval, const char *timestr, int duration)
{
    const char *p, *q;
    int64_t t, now64;
    time_t now;
    struct tm dt = { 0 }, tmbuf;
    int today = 0, negative = 0, microseconds = 0, suffix = 1000000;
    int i;
    static const char * const date_fmt[] = {
        "%Y - %m - %d",
        "%Y%m%d",
    };
    static const char * const time_fmt[] = {
        "%H:%M:%S",
        "%H%M%S",
    };
    static const char * const tz_fmt[] = {
        "%H:%M",
        "%H%M",
        "%H",
    };

    p = timestr;
    q = NULL;
    *timeval = INT64_MIN;
    if (!duration) {
        now64 = av_gettime();
        now = now64 / 1000000;

        if (!av_strcasecmp(timestr, "now")) {
            *timeval = now64;
            return 0;
        }

        /* parse the year-month-day part */
        for (i = 0; i < FF_ARRAY_ELEMS(date_fmt); i++) {
            q = av_small_strptime(p, date_fmt[i], &dt);
            if (q)
                break;
        }

        /* if the year-month-day part is missing, then take the
         * current year-month-day time */
        if (!q) {
            today = 1;
            q = p;
        }
        p = q;

        if (*p == 'T' || *p == 't')
            p++;
        else
            while (av_isspace(*p))
                p++;

        /* parse the hour-minute-second part */
        for (i = 0; i < FF_ARRAY_ELEMS(time_fmt); i++) {
            q = av_small_strptime(p, time_fmt[i], &dt);
            if (q)
                break;
        }
    } else {
        /* parse timestr as a duration */
        if (p[0] == '-') {
            negative = 1;
            ++p;
        }
        /* parse timestr as HH:MM:SS */
        q = av_small_strptime(p, "%J:%M:%S", &dt);
        if (!q) {
            /* parse timestr as MM:SS */
            q = av_small_strptime(p, "%M:%S", &dt);
            dt.tm_hour = 0;
        }
        if (!q) {
            char *o;
            /* parse timestr as S+ */
            errno = 0;
            t = strtoll(p, &o, 10);
            if (o == p) /* the parsing didn't succeed */
                return AVERROR(EINVAL);
            if (errno == ERANGE)
                return AVERROR(ERANGE);
            q = o;
        } else {
            t = dt.tm_hour * 3600 + dt.tm_min * 60 + dt.tm_sec;
        }
    }

    /* Now we have all the fields that we can get */
    if (!q)
        return AVERROR(EINVAL);

    /* parse the .m... part */
    if (*q == '.') {
        int n;
        q++;
        for (n = 100000; n >= 1; n /= 10, q++) {
            if (!av_isdigit(*q))
                break;
            microseconds += n * (*q - '0');
        }
        while (av_isdigit(*q))
            q++;
    }

    if (duration) {
        if (q[0] == 'm' && q[1] == 's') {
            suffix = 1000;
            microseconds /= 1000;
            q += 2;
        } else if (q[0] == 'u' && q[1] == 's') {
            suffix = 1;
            microseconds = 0;
            q += 2;
        } else if (*q == 's')
            q++;
    } else {
        int is_utc = *q == 'Z' || *q == 'z';
        int tzoffset = 0;
        q += is_utc;
        if (!today && !is_utc && (*q == '+' || *q == '-')) {
            struct tm tz = { 0 };
            int sign = (*q == '+' ? -1 : 1);
            q++;
            p = q;
            for (i = 0; i < FF_ARRAY_ELEMS(tz_fmt); i++) {
                q = av_small_strptime(p, tz_fmt[i], &tz);
                if (q)
                    break;
            }
            if (!q)
                return AVERROR(EINVAL);
            tzoffset = sign * (tz.tm_hour * 60 + tz.tm_min) * 60;
            is_utc = 1;
        }
        if (today) { /* fill in today's date */
            struct tm dt2 = is_utc ? *gmtime_r(&now, &tmbuf) : *localtime_r(&now, &tmbuf);
            dt2.tm_hour = dt.tm_hour;
            dt2.tm_min  = dt.tm_min;
            dt2.tm_sec  = dt.tm_sec;
            dt = dt2;
        }
        dt.tm_isdst = is_utc ? 0 : -1;
        t = is_utc ? av_timegm(&dt) : mktime(&dt);
        t += tzoffset;
    }

    /* Check that we are at the end of the string */
    if (*q)
        return AVERROR(EINVAL);

    if (INT64_MAX / suffix < t)
        return AVERROR(ERANGE);
    t *= suffix;
    if (INT64_MAX - microseconds < t)
        return AVERROR(ERANGE);
    t += microseconds;
    *timeval = negative ? -t : t;
    return 0;
}