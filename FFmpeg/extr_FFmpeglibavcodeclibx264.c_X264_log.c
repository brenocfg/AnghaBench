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
#define  AV_LOG_DEBUG 135 
#define  AV_LOG_ERROR 134 
#define  AV_LOG_INFO 133 
#define  AV_LOG_WARNING 132 
#define  X264_LOG_DEBUG 131 
#define  X264_LOG_ERROR 130 
#define  X264_LOG_INFO 129 
#define  X264_LOG_WARNING 128 
 int /*<<< orphan*/  av_vlog (void*,int const,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void X264_log(void *p, int level, const char *fmt, va_list args)
{
    static const int level_map[] = {
        [X264_LOG_ERROR]   = AV_LOG_ERROR,
        [X264_LOG_WARNING] = AV_LOG_WARNING,
        [X264_LOG_INFO]    = AV_LOG_INFO,
        [X264_LOG_DEBUG]   = AV_LOG_DEBUG
    };

    if (level < 0 || level > X264_LOG_DEBUG)
        return;

    av_vlog(p, level_map[level], fmt, args);
}