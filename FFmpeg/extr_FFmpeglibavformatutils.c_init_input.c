#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int flags; } ;
struct TYPE_11__ {int (* io_open ) (TYPE_2__*,int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ **) ;int avio_flags; int /*<<< orphan*/  format_probesize; TYPE_5__* iformat; int /*<<< orphan*/  pb; int /*<<< orphan*/  flags; } ;
struct TYPE_10__ {char const* member_0; int /*<<< orphan*/  member_2; int /*<<< orphan*/ * member_1; } ;
typedef  TYPE_1__ AVProbeData ;
typedef  TYPE_2__ AVFormatContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  AVFMT_FLAG_CUSTOM_IO ; 
 int AVFMT_NOFILE ; 
 int AVIO_FLAG_READ ; 
 int AVPROBE_SCORE_RETRY ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int av_probe_input_buffer2 (int /*<<< orphan*/ ,TYPE_5__**,char const*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* av_probe_input_format2 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int init_input(AVFormatContext *s, const char *filename,
                      AVDictionary **options)
{
    int ret;
    AVProbeData pd = { filename, NULL, 0 };
    int score = AVPROBE_SCORE_RETRY;

    if (s->pb) {
        s->flags |= AVFMT_FLAG_CUSTOM_IO;
        if (!s->iformat)
            return av_probe_input_buffer2(s->pb, &s->iformat, filename,
                                         s, 0, s->format_probesize);
        else if (s->iformat->flags & AVFMT_NOFILE)
            av_log(s, AV_LOG_WARNING, "Custom AVIOContext makes no sense and "
                                      "will be ignored with AVFMT_NOFILE format.\n");
        return 0;
    }

    if ((s->iformat && s->iformat->flags & AVFMT_NOFILE) ||
        (!s->iformat && (s->iformat = av_probe_input_format2(&pd, 0, &score))))
        return score;

    if ((ret = s->io_open(s, &s->pb, filename, AVIO_FLAG_READ | s->avio_flags, options)) < 0)
        return ret;

    if (s->iformat)
        return 0;
    return av_probe_input_buffer2(s->pb, &s->iformat, filename,
                                 s, 0, s->format_probesize);
}