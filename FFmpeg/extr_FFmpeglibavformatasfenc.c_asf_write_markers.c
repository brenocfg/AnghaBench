#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ int64_t ;
typedef  int int32_t ;
struct TYPE_11__ {int /*<<< orphan*/  time_base; int /*<<< orphan*/  start; int /*<<< orphan*/  metadata; } ;
struct TYPE_10__ {int /*<<< orphan*/  value; } ;
struct TYPE_9__ {int nb_chapters; TYPE_4__** chapters; int /*<<< orphan*/ * pb; int /*<<< orphan*/ * priv_data; } ;
struct TYPE_8__ {int member_0; int member_1; } ;
typedef  TYPE_1__ AVRational ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;
typedef  TYPE_3__ AVDictionaryEntry ;
typedef  TYPE_4__ AVChapter ;
typedef  int /*<<< orphan*/  ASFContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int PREROLL_TIME ; 
 TYPE_3__* av_dict_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 scalar_t__ av_rescale_q (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__) ; 
 int avio_close_dyn_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ avio_open_dyn_buf (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  avio_put_str16le (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wl16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wl64 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  end_header (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ff_asf_marker_header ; 
 int /*<<< orphan*/  ff_asf_reserved_4 ; 
 int /*<<< orphan*/  ff_put_guid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int get_send_time (int /*<<< orphan*/ *,scalar_t__,scalar_t__*) ; 
 scalar_t__ put_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int asf_write_markers(AVFormatContext *s)
{
    ASFContext *asf = s->priv_data;
    AVIOContext *pb = s->pb;
    int i;
    AVRational scale = {1, 10000000};
    int64_t hpos = put_header(pb, &ff_asf_marker_header);

    ff_put_guid(pb, &ff_asf_reserved_4);// ASF spec mandates this reserved value
    avio_wl32(pb, s->nb_chapters);     // markers count
    avio_wl16(pb, 0);                  // ASF spec mandates 0 for this
    avio_wl16(pb, 0);                  // name length 0, no name given

    for (i = 0; i < s->nb_chapters; i++) {
        AVChapter *c = s->chapters[i];
        AVDictionaryEntry *t = av_dict_get(c->metadata, "title", NULL, 0);
        int64_t pres_time = av_rescale_q(c->start, c->time_base, scale);
        uint64_t offset;
        int32_t send_time = get_send_time(asf, pres_time, &offset);
        int len = 0;
        uint8_t *buf;
        AVIOContext *dyn_buf;
        if (t) {
            if (avio_open_dyn_buf(&dyn_buf) < 0)
                return AVERROR(ENOMEM);
            avio_put_str16le(dyn_buf, t->value);
            len = avio_close_dyn_buf(dyn_buf, &buf);
        }
        avio_wl64(pb, offset);            // offset of the packet with send_time
        avio_wl64(pb, pres_time + PREROLL_TIME * 10000); // presentation time
        avio_wl16(pb, 12 + len);          // entry length
        avio_wl32(pb, send_time);         // send time
        avio_wl32(pb, 0);                 // flags, should be 0
        avio_wl32(pb, len / 2);           // marker desc length in WCHARS!
        if (t) {
            avio_write(pb, buf, len);     // marker desc
            av_freep(&buf);
        }
    }
    end_header(pb, hpos);
    return 0;
}