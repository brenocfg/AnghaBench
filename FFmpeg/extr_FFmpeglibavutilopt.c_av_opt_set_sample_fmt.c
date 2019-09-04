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
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;

/* Variables and functions */
 int /*<<< orphan*/  AV_OPT_TYPE_SAMPLE_FMT ; 
 int /*<<< orphan*/  AV_SAMPLE_FMT_NB ; 
 int set_format (void*,char const*,int,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int av_opt_set_sample_fmt(void *obj, const char *name, enum AVSampleFormat fmt, int search_flags)
{
    return set_format(obj, name, fmt, search_flags, AV_OPT_TYPE_SAMPLE_FMT, "sample", AV_SAMPLE_FMT_NB);
}