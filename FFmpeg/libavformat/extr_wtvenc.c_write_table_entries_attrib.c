#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {size_t stream_index; scalar_t__ size; int /*<<< orphan*/  data; } ;
struct TYPE_11__ {TYPE_9__ thumbnail; } ;
typedef  TYPE_1__ WtvContext ;
struct TYPE_14__ {char* value; int /*<<< orphan*/  key; } ;
struct TYPE_13__ {TYPE_2__** streams; int /*<<< orphan*/  metadata; int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
struct TYPE_12__ {int /*<<< orphan*/  metadata; } ;
typedef  TYPE_2__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ AVDictionaryEntry ;

/* Variables and functions */
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 int /*<<< orphan*/  attachment_value_size (TYPE_9__*,TYPE_4__*) ; 
 TYPE_4__* av_dict_get (int /*<<< orphan*/ ,char*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_put_str16le (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ff_asf_metadata_conv ; 
 int /*<<< orphan*/  ff_metadata_conv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_standardize_creation_time (TYPE_3__*) ; 
 int /*<<< orphan*/  write_metadata_header (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  write_tag_int32 (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void write_table_entries_attrib(AVFormatContext *s)
{
    WtvContext *wctx = s->priv_data;
    AVIOContext *pb = s->pb;
    AVDictionaryEntry *tag = 0;

    ff_standardize_creation_time(s);
    //FIXME: translate special tags (e.g. WM/Bitrate) to binary representation
    ff_metadata_conv(&s->metadata, ff_asf_metadata_conv, NULL);
    while ((tag = av_dict_get(s->metadata, "", tag, AV_DICT_IGNORE_SUFFIX)))
        write_tag(pb, tag->key, tag->value);

    if (wctx->thumbnail.size) {
        AVStream *st = s->streams[wctx->thumbnail.stream_index];
        tag = av_dict_get(st->metadata, "title", NULL, 0);
        write_metadata_header(pb, 2, "WM/Picture", attachment_value_size(&wctx->thumbnail, tag));

        avio_put_str16le(pb, "image/jpeg");
        avio_w8(pb, 0x10);
        avio_put_str16le(pb, tag ? tag->value : "");

        avio_wl32(pb, wctx->thumbnail.size);
        avio_write(pb, wctx->thumbnail.data, wctx->thumbnail.size);

        write_tag_int32(pb, "WM/MediaThumbType", 2);
    }
}