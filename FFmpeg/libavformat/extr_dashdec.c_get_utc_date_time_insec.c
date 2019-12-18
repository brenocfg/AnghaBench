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
typedef  int /*<<< orphan*/  uint64_t ;
struct tm {int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_min; int tm_sec; } ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  av_timegm (struct tm*) ; 
 int sscanf (char const*,char*,int*,int*,int*,int*,int*,float*) ; 

__attribute__((used)) static uint64_t get_utc_date_time_insec(AVFormatContext *s, const char *datetime)
{
    struct tm timeinfo;
    int year = 0;
    int month = 0;
    int day = 0;
    int hour = 0;
    int minute = 0;
    int ret = 0;
    float second = 0.0;

    /* ISO-8601 date parser */
    if (!datetime)
        return 0;

    ret = sscanf(datetime, "%d-%d-%dT%d:%d:%fZ", &year, &month, &day, &hour, &minute, &second);
    /* year, month, day, hour, minute, second  6 arguments */
    if (ret != 6) {
        av_log(s, AV_LOG_WARNING, "get_utc_date_time_insec get a wrong time format\n");
    }
    timeinfo.tm_year = year - 1900;
    timeinfo.tm_mon  = month - 1;
    timeinfo.tm_mday = day;
    timeinfo.tm_hour = hour;
    timeinfo.tm_min  = minute;
    timeinfo.tm_sec  = (int)second;

    return av_timegm(&timeinfo);
}