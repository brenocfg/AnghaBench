#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_9__ {int /*<<< orphan*/  url; TYPE_2__* priv_data; } ;
struct TYPE_7__ {int /*<<< orphan*/  filename; } ;
struct TYPE_8__ {int segment_idx_wrap; int segment_idx; char* entry_prefix; TYPE_1__ cur_entry; scalar_t__ use_strftime; TYPE_3__* avf; } ;
typedef  TYPE_2__ SegmentContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 char* av_basename (int /*<<< orphan*/ ) ; 
 scalar_t__ av_get_frame_filename (char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 int av_reallocp (int /*<<< orphan*/ *,size_t) ; 
 char* av_strdup (char*) ; 
 int /*<<< orphan*/  ff_format_set_url (TYPE_3__*,char*) ; 
 struct tm* localtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,size_t,char*,char*,char*) ; 
 int /*<<< orphan*/  strftime (char*,int,int /*<<< orphan*/ ,struct tm*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_segment_filename(AVFormatContext *s)
{
    SegmentContext *seg = s->priv_data;
    AVFormatContext *oc = seg->avf;
    size_t size;
    int ret;
    char buf[1024];
    char *new_name;

    if (seg->segment_idx_wrap)
        seg->segment_idx %= seg->segment_idx_wrap;
    if (seg->use_strftime) {
        time_t now0;
        struct tm *tm, tmpbuf;
        time(&now0);
        tm = localtime_r(&now0, &tmpbuf);
        if (!strftime(buf, sizeof(buf), s->url, tm)) {
            av_log(oc, AV_LOG_ERROR, "Could not get segment filename with strftime\n");
            return AVERROR(EINVAL);
        }
    } else if (av_get_frame_filename(buf, sizeof(buf),
                                     s->url, seg->segment_idx) < 0) {
        av_log(oc, AV_LOG_ERROR, "Invalid segment filename template '%s'\n", s->url);
        return AVERROR(EINVAL);
    }
    new_name = av_strdup(buf);
    if (!new_name)
        return AVERROR(ENOMEM);
    ff_format_set_url(oc, new_name);

    /* copy modified name in list entry */
    size = strlen(av_basename(oc->url)) + 1;
    if (seg->entry_prefix)
        size += strlen(seg->entry_prefix);

    if ((ret = av_reallocp(&seg->cur_entry.filename, size)) < 0)
        return ret;
    snprintf(seg->cur_entry.filename, size, "%s%s",
             seg->entry_prefix ? seg->entry_prefix : "",
             av_basename(oc->url));

    return 0;
}