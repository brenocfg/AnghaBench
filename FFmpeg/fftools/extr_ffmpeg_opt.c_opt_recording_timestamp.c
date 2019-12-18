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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  OptionsContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 struct tm* gmtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  options ; 
 int /*<<< orphan*/  parse_option (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int parse_time_or_die (char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 

__attribute__((used)) static int opt_recording_timestamp(void *optctx, const char *opt, const char *arg)
{
    OptionsContext *o = optctx;
    char buf[128];
    int64_t recording_timestamp = parse_time_or_die(opt, arg, 0) / 1E6;
    struct tm time = *gmtime((time_t*)&recording_timestamp);
    if (!strftime(buf, sizeof(buf), "creation_time=%Y-%m-%dT%H:%M:%S%z", &time))
        return -1;
    parse_option(o, "metadata", buf, options);

    av_log(NULL, AV_LOG_WARNING, "%s is deprecated, set the 'creation_time' metadata "
                                 "tag instead.\n", opt);
    return 0;
}