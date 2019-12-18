#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  stream_index; scalar_t__ size; int /*<<< orphan*/  data; TYPE_2__* buf; } ;
struct TYPE_13__ {TYPE_8__ attached_pic; int /*<<< orphan*/  index; int /*<<< orphan*/  metadata; TYPE_1__* codecpar; int /*<<< orphan*/  disposition; } ;
struct TYPE_12__ {TYPE_3__* data; int /*<<< orphan*/  tag; struct TYPE_12__* next; } ;
struct TYPE_11__ {TYPE_2__* buf; scalar_t__* type; scalar_t__* description; int /*<<< orphan*/  id; } ;
struct TYPE_10__ {scalar_t__ size; int /*<<< orphan*/  data; } ;
struct TYPE_9__ {int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_3__ ID3v2ExtraMetaAPIC ;
typedef  TYPE_4__ ID3v2ExtraMeta ;
typedef  TYPE_5__ AVStream ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_CODEC_ID_PNG ; 
 int /*<<< orphan*/  AV_DISPOSITION_ATTACHED_PIC ; 
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 scalar_t__ AV_RB64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ PNGSIG ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,char*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_init_packet (TYPE_8__*) ; 
 TYPE_5__* avformat_new_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

int ff_id3v2_parse_apic(AVFormatContext *s, ID3v2ExtraMeta **extra_meta)
{
    ID3v2ExtraMeta *cur;

    for (cur = *extra_meta; cur; cur = cur->next) {
        ID3v2ExtraMetaAPIC *apic;
        AVStream *st;

        if (strcmp(cur->tag, "APIC"))
            continue;
        apic = cur->data;

        if (!(st = avformat_new_stream(s, NULL)))
            return AVERROR(ENOMEM);

        st->disposition      |= AV_DISPOSITION_ATTACHED_PIC;
        st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
        st->codecpar->codec_id   = apic->id;

        if (AV_RB64(apic->buf->data) == PNGSIG)
            st->codecpar->codec_id = AV_CODEC_ID_PNG;

        if (apic->description[0])
            av_dict_set(&st->metadata, "title", apic->description, 0);

        av_dict_set(&st->metadata, "comment", apic->type, 0);

        av_init_packet(&st->attached_pic);
        st->attached_pic.buf          = apic->buf;
        st->attached_pic.data         = apic->buf->data;
        st->attached_pic.size         = apic->buf->size - AV_INPUT_BUFFER_PADDING_SIZE;
        st->attached_pic.stream_index = st->index;
        st->attached_pic.flags       |= AV_PKT_FLAG_KEY;

        apic->buf = NULL;
    }

    return 0;
}