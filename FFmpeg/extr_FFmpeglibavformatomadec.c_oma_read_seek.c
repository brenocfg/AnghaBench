#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct AVFormatContext {int /*<<< orphan*/  pb; TYPE_3__** streams; TYPE_2__* priv_data; } ;
typedef  int int64_t ;
struct TYPE_6__ {TYPE_1__* codecpar; } ;
struct TYPE_5__ {scalar_t__ content_start; int /*<<< orphan*/  iv; int /*<<< orphan*/  encrypted; } ;
struct TYPE_4__ {scalar_t__ codec_id; } ;
typedef  TYPE_2__ OMAContext ;
typedef  TYPE_3__ AVStream ;

/* Variables and functions */
 int AVERROR_EOF ; 
 scalar_t__ AV_CODEC_ID_ATRAC3AL ; 
 scalar_t__ AV_CODEC_ID_ATRAC3PAL ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int avio_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int avio_seek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ ) ; 
 int ff_pcm_read_seek (struct AVFormatContext*,int,int,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int oma_read_seek(struct AVFormatContext *s,
                         int stream_index, int64_t timestamp, int flags)
{
    OMAContext *oc = s->priv_data;
    AVStream *st = s->streams[0];
    int64_t err;

    if (st->codecpar->codec_id == AV_CODEC_ID_ATRAC3PAL ||
        st->codecpar->codec_id == AV_CODEC_ID_ATRAC3AL)
        return -1;

    err = ff_pcm_read_seek(s, stream_index, timestamp, flags);
    if (!oc->encrypted)
        return err;

    /* readjust IV for CBC */
    if (err || avio_tell(s->pb) < oc->content_start)
        goto wipe;
    if ((err = avio_seek(s->pb, -8, SEEK_CUR)) < 0)
        goto wipe;
    if ((err = avio_read(s->pb, oc->iv, 8)) < 8) {
        if (err >= 0)
            err = AVERROR_EOF;
        goto wipe;
    }

    return 0;
wipe:
    memset(oc->iv, 0, 8);
    return err;
}