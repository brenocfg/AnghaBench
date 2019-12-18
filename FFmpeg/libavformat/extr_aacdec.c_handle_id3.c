#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  event_flags; int /*<<< orphan*/  metadata; int /*<<< orphan*/  pb; } ;
struct TYPE_7__ {scalar_t__ size; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  ID3v2ExtraMeta ;
typedef  TYPE_1__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  AVFMT_EVENT_FLAG_METADATA_UPDATED ; 
 int /*<<< orphan*/  ID3v2_DEFAULT_MAGIC ; 
 int av_append_packet (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__) ; 
 int av_dict_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_1__*) ; 
 int /*<<< orphan*/  ff_id3v2_free_extra_meta (int /*<<< orphan*/ **) ; 
 int ff_id3v2_parse_priv_dict (int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ff_id3v2_read_dict (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ ff_id3v2_tag_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffio_init_context (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int handle_id3(AVFormatContext *s, AVPacket *pkt)
{
    AVDictionary *metadata = NULL;
    AVIOContext ioctx;
    ID3v2ExtraMeta *id3v2_extra_meta = NULL;
    int ret;

    ret = av_append_packet(s->pb, pkt, ff_id3v2_tag_len(pkt->data) - pkt->size);
    if (ret < 0) {
        av_packet_unref(pkt);
        return ret;
    }

    ffio_init_context(&ioctx, pkt->data, pkt->size, 0, NULL, NULL, NULL, NULL);
    ff_id3v2_read_dict(&ioctx, &metadata, ID3v2_DEFAULT_MAGIC, &id3v2_extra_meta);
    if ((ret = ff_id3v2_parse_priv_dict(&metadata, &id3v2_extra_meta)) < 0)
        goto error;

    if (metadata) {
        if ((ret = av_dict_copy(&s->metadata, metadata, 0)) < 0)
            goto error;
        s->event_flags |= AVFMT_EVENT_FLAG_METADATA_UPDATED;
    }

error:
    av_packet_unref(pkt);
    ff_id3v2_free_extra_meta(&id3v2_extra_meta);
    av_dict_free(&metadata);

    return ret;
}