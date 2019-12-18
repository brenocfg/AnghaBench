#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_12__ {int /*<<< orphan*/  metadata; int /*<<< orphan*/  time_base; int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct TYPE_11__ {int /*<<< orphan*/ * pb; TYPE_4__** chapters; } ;
struct TYPE_10__ {int member_0; int member_1; } ;
struct TYPE_9__ {int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ ID3v2EncContext ;
typedef  TYPE_2__ AVRational ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ AVChapter ;

/* Variables and functions */
 scalar_t__ ID3v2_HEADER_SIZE ; 
 int MKBETAG (char,char,char,char) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int av_rescale_q (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__ const) ; 
 int avio_close_dyn_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int avio_open_dyn_buf (int /*<<< orphan*/ **) ; 
 scalar_t__ avio_put_str (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int write_metadata (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int) ; 

__attribute__((used)) static int write_chapter(AVFormatContext *s, ID3v2EncContext *id3, int id, int enc)
{
    const AVRational time_base = {1, 1000};
    AVChapter *ch = s->chapters[id];
    uint8_t *dyn_buf = NULL;
    AVIOContext *dyn_bc = NULL;
    char name[123];
    int len, start, end, ret;

    if ((ret = avio_open_dyn_buf(&dyn_bc)) < 0)
        goto fail;

    start = av_rescale_q(ch->start, ch->time_base, time_base);
    end   = av_rescale_q(ch->end,   ch->time_base, time_base);

    snprintf(name, 122, "ch%d", id);
    id3->len += avio_put_str(dyn_bc, name);
    avio_wb32(dyn_bc, start);
    avio_wb32(dyn_bc, end);
    avio_wb32(dyn_bc, 0xFFFFFFFFu);
    avio_wb32(dyn_bc, 0xFFFFFFFFu);

    if ((ret = write_metadata(dyn_bc, &ch->metadata, id3, enc)) < 0)
        goto fail;

    len = avio_close_dyn_buf(dyn_bc, &dyn_buf);
    id3->len += 16 + ID3v2_HEADER_SIZE;

    avio_wb32(s->pb, MKBETAG('C', 'H', 'A', 'P'));
    avio_wb32(s->pb, len);
    avio_wb16(s->pb, 0);
    avio_write(s->pb, dyn_buf, len);

fail:
    if (dyn_bc && !dyn_buf)
        avio_close_dyn_buf(dyn_bc, &dyn_buf);
    av_freep(&dyn_buf);

    return ret;
}