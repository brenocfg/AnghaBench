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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int AV_LOG_DEBUG ; 
 int AV_LOG_ERROR ; 
 int AV_LOG_FATAL ; 
 int AV_LOG_INFO ; 
 int AV_LOG_VERBOSE ; 
 int AV_LOG_WARNING ; 
#define  RTMP_LOGCRIT 133 
#define  RTMP_LOGDEBUG 132 
#define  RTMP_LOGDEBUG2 131 
#define  RTMP_LOGERROR 130 
#define  RTMP_LOGINFO 129 
#define  RTMP_LOGWARNING 128 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  av_vlog (int /*<<< orphan*/ *,int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtmp_log(int level, const char *fmt, va_list args)
{
    switch (level) {
    default:
    case RTMP_LOGCRIT:    level = AV_LOG_FATAL;   break;
    case RTMP_LOGERROR:   level = AV_LOG_ERROR;   break;
    case RTMP_LOGWARNING: level = AV_LOG_WARNING; break;
    case RTMP_LOGINFO:    level = AV_LOG_INFO;    break;
    case RTMP_LOGDEBUG:   level = AV_LOG_VERBOSE; break;
    case RTMP_LOGDEBUG2:  level = AV_LOG_DEBUG;   break;
    }

    av_vlog(NULL, level, fmt, args);
    av_log(NULL, level, "\n");
}