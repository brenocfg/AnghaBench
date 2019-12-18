#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int AV_SAMPLE_FMT_NB ; 
 int AV_SAMPLE_FMT_NONE ; 
 TYPE_1__* sample_fmt_info ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

enum AVSampleFormat av_get_sample_fmt(const char *name)
{
    int i;

    for (i = 0; i < AV_SAMPLE_FMT_NB; i++)
        if (!strcmp(sample_fmt_info[i].name, name))
            return i;
    return AV_SAMPLE_FMT_NONE;
}