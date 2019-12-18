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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR_EXTERNAL ; 
 int av_dict_set (int /*<<< orphan*/ **,char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_strlcatf (char*,int,char*,int) ; 
 struct tm* gmtime_r (int*,struct tm*) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 

int avpriv_dict_set_timestamp(AVDictionary **dict, const char *key, int64_t timestamp)
{
    time_t seconds = timestamp / 1000000;
    struct tm *ptm, tmbuf;
    ptm = gmtime_r(&seconds, &tmbuf);
    if (ptm) {
        char buf[32];
        if (!strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%S", ptm))
            return AVERROR_EXTERNAL;
        av_strlcatf(buf, sizeof(buf), ".%06dZ", (int)(timestamp % 1000000));
        return av_dict_set(dict, key, buf, 0);
    } else {
        return AVERROR_EXTERNAL;
    }
}