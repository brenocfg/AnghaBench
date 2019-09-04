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

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_FATAL ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  av_max_alloc (size_t) ; 
 int /*<<< orphan*/  exit_program (int) ; 
 size_t strtol (char const*,char**,int) ; 

int opt_max_alloc(void *optctx, const char *opt, const char *arg)
{
    char *tail;
    size_t max;

    max = strtol(arg, &tail, 10);
    if (*tail) {
        av_log(NULL, AV_LOG_FATAL, "Invalid max_alloc \"%s\".\n", arg);
        exit_program(1);
    }
    av_max_alloc(max);
    return 0;
}