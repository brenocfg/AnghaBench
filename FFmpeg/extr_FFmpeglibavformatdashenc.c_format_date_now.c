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
struct tm {int dummy; } ;
typedef  int int64_t ;

/* Variables and functions */
 int av_gettime () ; 
 struct tm* gmtime_r (int const*,struct tm*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void format_date_now(char *buf, int size)
{
    struct tm *ptm, tmbuf;
    int64_t time_us = av_gettime();
    int64_t time_ms = time_us / 1000;
    const time_t time_s = time_ms / 1000;
    int millisec = time_ms - (time_s * 1000);
    ptm = gmtime_r(&time_s, &tmbuf);
    if (ptm) {
        int len;
        if (!strftime(buf, size, "%Y-%m-%dT%H:%M:%S", ptm)) {
            buf[0] = '\0';
            return;
        }
        len = strlen(buf);
        snprintf(buf + len, size - len, ".%03dZ", millisec);
    }
}