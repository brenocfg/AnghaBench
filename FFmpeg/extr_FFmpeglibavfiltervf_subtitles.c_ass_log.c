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
 scalar_t__ FF_ARRAY_ELEMS (int*) ; 
 int* ass_libavfilter_log_level_map ; 
 int av_clip (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  av_log (void*,int const,char*) ; 
 int /*<<< orphan*/  av_vlog (void*,int const,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ass_log(int ass_level, const char *fmt, va_list args, void *ctx)
{
    const int ass_level_clip = av_clip(ass_level, 0,
        FF_ARRAY_ELEMS(ass_libavfilter_log_level_map) - 1);
    const int level = ass_libavfilter_log_level_map[ass_level_clip];

    av_vlog(ctx, level, fmt, args);
    av_log(ctx, level, "\n");
}