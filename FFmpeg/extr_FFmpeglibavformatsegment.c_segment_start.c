#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ seekable; } ;
struct TYPE_15__ {int (* io_open ) (TYPE_3__*,TYPE_5__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;TYPE_2__* priv_data; TYPE_1__* oformat; TYPE_5__* pb; int /*<<< orphan*/  url; } ;
struct TYPE_14__ {int segment_idx; int segment_idx_wrap; scalar_t__ segment_frame_count; int /*<<< orphan*/  format_options; int /*<<< orphan*/  individual_header_trailer; int /*<<< orphan*/  segment_idx_wrap_nb; TYPE_3__* avf; } ;
struct TYPE_13__ {scalar_t__ priv_class; } ;
typedef  TYPE_2__ SegmentContext ;
typedef  TYPE_3__ AVFormatContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  AVIO_FLAG_WRITE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_dict_copy (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ **,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_opt_set (TYPE_2__*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avformat_free_context (TYPE_3__*) ; 
 int avformat_write_header (TYPE_3__*,int /*<<< orphan*/ **) ; 
 int segment_mux_init (TYPE_3__*) ; 
 int set_segment_filename (TYPE_3__*) ; 
 int stub1 (TYPE_3__*,TYPE_5__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int segment_start(AVFormatContext *s, int write_header)
{
    SegmentContext *seg = s->priv_data;
    AVFormatContext *oc = seg->avf;
    int err = 0;

    if (write_header) {
        avformat_free_context(oc);
        seg->avf = NULL;
        if ((err = segment_mux_init(s)) < 0)
            return err;
        oc = seg->avf;
    }

    seg->segment_idx++;
    if ((seg->segment_idx_wrap) && (seg->segment_idx % seg->segment_idx_wrap == 0))
        seg->segment_idx_wrap_nb++;

    if ((err = set_segment_filename(s)) < 0)
        return err;

    if ((err = s->io_open(s, &oc->pb, oc->url, AVIO_FLAG_WRITE, NULL)) < 0) {
        av_log(s, AV_LOG_ERROR, "Failed to open segment '%s'\n", oc->url);
        return err;
    }
    if (!seg->individual_header_trailer)
        oc->pb->seekable = 0;

    if (oc->oformat->priv_class && oc->priv_data)
        av_opt_set(oc->priv_data, "mpegts_flags", "+resend_headers", 0);

    if (write_header) {
        AVDictionary *options = NULL;
        av_dict_copy(&options, seg->format_options, 0);
        av_dict_set(&options, "fflags", "-autobsf", 0);
        err = avformat_write_header(oc, &options);
        av_dict_free(&options);
        if (err < 0)
            return err;
    }

    seg->segment_frame_count = 0;
    return 0;
}