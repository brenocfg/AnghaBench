#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_7__ {int predefined_SLConfigDescriptor_seen; int /*<<< orphan*/  s; int /*<<< orphan*/  pb; TYPE_2__* active_descr; } ;
struct TYPE_5__ {int use_au_start; int use_au_end; int use_rand_acc_pt; int use_padding; int use_timestamps; int use_idle; int timestamp_len; int ocr_len; int au_len; int degr_prior_len; int au_seq_num_len; int packet_seq_num_len; void* inst_bitrate_len; int /*<<< orphan*/  timestamp_res; } ;
struct TYPE_6__ {TYPE_1__ sl; } ;
typedef  TYPE_2__ Mp4Descr ;
typedef  TYPE_3__ MP4DescrParseContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 void* avio_r8 (int /*<<< orphan*/ *) ; 
 int avio_rb16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_rb32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avpriv_report_missing_feature (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int parse_MP4SLDescrTag(MP4DescrParseContext *d, int64_t off, int len)
{
    Mp4Descr *descr = d->active_descr;
    int predefined;
    if (!descr)
        return AVERROR_INVALIDDATA;

#define R8_CHECK_CLIP_MAX(dst, maxv) do {                       \
    descr->sl.dst = avio_r8(&d->pb);                            \
    if (descr->sl.dst > maxv) {                                 \
        descr->sl.dst = maxv;                                   \
        return AVERROR_INVALIDDATA;                             \
    }                                                           \
} while (0)

    predefined = avio_r8(&d->pb);
    if (!predefined) {
        int lengths;
        int flags = avio_r8(&d->pb);
        descr->sl.use_au_start    = !!(flags & 0x80);
        descr->sl.use_au_end      = !!(flags & 0x40);
        descr->sl.use_rand_acc_pt = !!(flags & 0x20);
        descr->sl.use_padding     = !!(flags & 0x08);
        descr->sl.use_timestamps  = !!(flags & 0x04);
        descr->sl.use_idle        = !!(flags & 0x02);
        descr->sl.timestamp_res   = avio_rb32(&d->pb);
        avio_rb32(&d->pb);
        R8_CHECK_CLIP_MAX(timestamp_len, 63);
        R8_CHECK_CLIP_MAX(ocr_len,       63);
        R8_CHECK_CLIP_MAX(au_len,        31);
        descr->sl.inst_bitrate_len   = avio_r8(&d->pb);
        lengths                      = avio_rb16(&d->pb);
        descr->sl.degr_prior_len     = lengths >> 12;
        descr->sl.au_seq_num_len     = (lengths >> 7) & 0x1f;
        descr->sl.packet_seq_num_len = (lengths >> 2) & 0x1f;
    } else if (!d->predefined_SLConfigDescriptor_seen){
        avpriv_report_missing_feature(d->s, "Predefined SLConfigDescriptor");
        d->predefined_SLConfigDescriptor_seen = 1;
    }
    return 0;
}