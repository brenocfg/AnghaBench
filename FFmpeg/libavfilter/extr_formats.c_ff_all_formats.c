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
typedef  enum AVMediaType { ____Placeholder_AVMediaType } AVMediaType ;
typedef  int /*<<< orphan*/  AVPixFmtDescriptor ;
typedef  int /*<<< orphan*/  AVFilterFormats ;

/* Variables and functions */
 int AVMEDIA_TYPE_AUDIO ; 
 int AVMEDIA_TYPE_VIDEO ; 
 scalar_t__ av_get_sample_fmt_name (int) ; 
 int av_pix_fmt_desc_get_id (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * av_pix_fmt_desc_next (int /*<<< orphan*/  const*) ; 
 scalar_t__ ff_add_format (int /*<<< orphan*/ **,int) ; 

AVFilterFormats *ff_all_formats(enum AVMediaType type)
{
    AVFilterFormats *ret = NULL;

    if (type == AVMEDIA_TYPE_VIDEO) {
        const AVPixFmtDescriptor *desc = NULL;
        while ((desc = av_pix_fmt_desc_next(desc))) {
            if (ff_add_format(&ret, av_pix_fmt_desc_get_id(desc)) < 0)
                return NULL;
        }
    } else if (type == AVMEDIA_TYPE_AUDIO) {
        enum AVSampleFormat fmt = 0;
        while (av_get_sample_fmt_name(fmt)) {
            if (ff_add_format(&ret, fmt) < 0)
                return NULL;
            fmt++;
        }
    }

    return ret;
}