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
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  ENOMEM ; 
 int RTLD_LOCAL ; 
 int RTLD_NOW ; 
 int /*<<< orphan*/  SLIBSUF ; 
 char* av_asprintf (char*,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 void* dlopen (char*,int) ; 

__attribute__((used)) static int load_path(AVFilterContext *ctx, void **handle_ptr, const char *prefix, const char *name)
{
    char *path = av_asprintf("%s%s%s", prefix, name, SLIBSUF);
    if (!path)
        return AVERROR(ENOMEM);
    av_log(ctx, AV_LOG_DEBUG, "Looking for frei0r effect in '%s'.\n", path);
    *handle_ptr = dlopen(path, RTLD_NOW|RTLD_LOCAL);
    av_free(path);
    return 0;
}