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
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_14__ {size_t stream_index; scalar_t__ size; } ;
struct TYPE_10__ {TYPE_8__ thumbnail; } ;
typedef  TYPE_1__ WtvContext ;
struct TYPE_13__ {char* key; int /*<<< orphan*/  value; } ;
struct TYPE_12__ {TYPE_2__** streams; int /*<<< orphan*/  metadata; int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
struct TYPE_11__ {int /*<<< orphan*/  metadata; } ;
typedef  TYPE_2__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ AVDictionaryEntry ;

/* Variables and functions */
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 scalar_t__ attachment_value_size (TYPE_8__*,TYPE_4__*) ; 
 TYPE_4__* av_dict_get (int /*<<< orphan*/ ,char*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wl64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ metadata_header_size (char*) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_table_redirector_legacy_attrib(AVFormatContext *s)
{
    WtvContext *wctx = s->priv_data;
    AVIOContext *pb = s->pb;
    AVDictionaryEntry *tag = 0;
    int64_t pos = 0;

    //FIXME: translate special tags to binary representation
    while ((tag = av_dict_get(s->metadata, "", tag, AV_DICT_IGNORE_SUFFIX))) {
        avio_wl64(pb, pos);
        pos += metadata_header_size(tag->key) + strlen(tag->value)*2 + 2;
    }

    if (wctx->thumbnail.size) {
        AVStream *st = s->streams[wctx->thumbnail.stream_index];
        avio_wl64(pb, pos);
        pos += metadata_header_size("WM/Picture") + attachment_value_size(&wctx->thumbnail, av_dict_get(st->metadata, "title", NULL, 0));

        avio_wl64(pb, pos);
        pos += metadata_header_size("WM/MediaThumbType") + 4;
    }
}