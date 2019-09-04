#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_3__* priv_data; } ;
struct TYPE_14__ {int /*<<< orphan*/  time_base; TYPE_1__* codecpar; } ;
struct TYPE_12__ {int /*<<< orphan*/  num; int /*<<< orphan*/  den; } ;
struct TYPE_13__ {int chars_per_frame; TYPE_2__ framerate; int /*<<< orphan*/  width; } ;
struct TYPE_11__ {int width; int height; int /*<<< orphan*/  codec_type; scalar_t__ codec_tag; } ;
typedef  TYPE_3__ BinDemuxContext ;
typedef  TYPE_4__ AVStream ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  INT_MAX ; 
 int av_clip (int,int,int /*<<< orphan*/ ) ; 
 int av_q2d (int /*<<< orphan*/ ) ; 
 TYPE_4__* avformat_new_stream (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static AVStream * init_stream(AVFormatContext *s)
{
    BinDemuxContext *bin = s->priv_data;
    AVStream *st = avformat_new_stream(s, NULL);
    if (!st)
        return NULL;
    st->codecpar->codec_tag   = 0;
    st->codecpar->codec_type  = AVMEDIA_TYPE_VIDEO;

    if (!bin->width) {
        st->codecpar->width  = (80<<3);
        st->codecpar->height = (25<<4);
    }

    avpriv_set_pts_info(st, 60, bin->framerate.den, bin->framerate.num);

    /* simulate tty display speed */
    bin->chars_per_frame = av_clip(av_q2d(st->time_base) * bin->chars_per_frame, 1, INT_MAX);

    return st;
}