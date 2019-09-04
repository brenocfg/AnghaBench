#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_14__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
struct TYPE_24__ {size_t stream_idx; int fileuid; } ;
typedef  TYPE_3__ mkv_attachment ;
typedef  int /*<<< orphan*/  ebml_master ;
struct TYPE_28__ {int id; int /*<<< orphan*/  metadata; } ;
struct TYPE_27__ {int nb_streams; int nb_chapters; TYPE_14__* pb; TYPE_5__** streams; TYPE_7__** chapters; int /*<<< orphan*/  metadata; TYPE_4__* priv_data; } ;
struct TYPE_26__ {int /*<<< orphan*/  metadata; TYPE_1__* codecpar; } ;
struct TYPE_20__ {scalar_t__ pos; } ;
struct TYPE_25__ {scalar_t__ mode; int chapter_id_offset; TYPE_10__ tags; int /*<<< orphan*/ * tags_bc; int /*<<< orphan*/  is_live; TYPE_2__* attachments; scalar_t__ have_attachments; int /*<<< orphan*/ * stream_duration_offsets; } ;
struct TYPE_23__ {int num_entries; TYPE_3__* entries; } ;
struct TYPE_22__ {scalar_t__ codec_type; } ;
struct TYPE_21__ {int seekable; } ;
typedef  TYPE_4__ MatroskaMuxContext ;
typedef  TYPE_5__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_6__ AVFormatContext ;
typedef  TYPE_7__ AVChapter ;

/* Variables and functions */
 int AVIO_SEEKABLE_NORMAL ; 
 scalar_t__ AVMEDIA_TYPE_ATTACHMENT ; 
 int /*<<< orphan*/  MATROSKA_ID_SIMPLETAG ; 
 int /*<<< orphan*/  MATROSKA_ID_TAGNAME ; 
 int /*<<< orphan*/  MATROSKA_ID_TAGTARGETS_ATTACHUID ; 
 int /*<<< orphan*/  MATROSKA_ID_TAGTARGETS_CHAPTERUID ; 
 int /*<<< orphan*/  MATROSKA_ID_TAGTARGETS_TRACKUID ; 
 scalar_t__ MODE_WEBM ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  end_ebml_master (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_ebml_master_crc32 (TYPE_14__*,int /*<<< orphan*/ **,TYPE_4__*,TYPE_10__) ; 
 int /*<<< orphan*/  end_ebml_master_crc32_preliminary (TYPE_14__*,int /*<<< orphan*/ **,TYPE_4__*,TYPE_10__) ; 
 int /*<<< orphan*/  ff_metadata_conv_ctx (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_mkv_metadata_conv ; 
 scalar_t__ mkv_check_tag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mkv_write_tag (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_10__*) ; 
 int /*<<< orphan*/  mkv_write_tag_targets (TYPE_6__*,int /*<<< orphan*/ ,int,TYPE_10__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_ebml_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  put_ebml_void (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  start_ebml_master (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mkv_write_tags(AVFormatContext *s)
{
    MatroskaMuxContext *mkv = s->priv_data;
    int i, ret;

    ff_metadata_conv_ctx(s, ff_mkv_metadata_conv, NULL);

    if (mkv_check_tag(s->metadata, 0)) {
        ret = mkv_write_tag(s, s->metadata, 0, 0, &mkv->tags);
        if (ret < 0) return ret;
    }

    for (i = 0; i < s->nb_streams; i++) {
        AVStream *st = s->streams[i];

        if (st->codecpar->codec_type == AVMEDIA_TYPE_ATTACHMENT)
            continue;

        if (!mkv_check_tag(st->metadata, MATROSKA_ID_TAGTARGETS_TRACKUID))
            continue;

        ret = mkv_write_tag(s, st->metadata, MATROSKA_ID_TAGTARGETS_TRACKUID, i + 1, &mkv->tags);
        if (ret < 0) return ret;
    }

    if ((s->pb->seekable & AVIO_SEEKABLE_NORMAL) && !mkv->is_live) {
        for (i = 0; i < s->nb_streams; i++) {
            AVIOContext *pb;
            AVStream *st = s->streams[i];
            ebml_master tag_target;
            ebml_master tag;

            if (st->codecpar->codec_type == AVMEDIA_TYPE_ATTACHMENT)
                continue;

            mkv_write_tag_targets(s, MATROSKA_ID_TAGTARGETS_TRACKUID, i + 1, &mkv->tags, &tag_target);
            pb = mkv->tags_bc;

            tag = start_ebml_master(pb, MATROSKA_ID_SIMPLETAG, 0);
            put_ebml_string(pb, MATROSKA_ID_TAGNAME, "DURATION");
            mkv->stream_duration_offsets[i] = avio_tell(pb);

            // Reserve space to write duration as a 20-byte string.
            // 2 (ebml id) + 1 (data size) + 20 (data)
            put_ebml_void(pb, 23);
            end_ebml_master(pb, tag);
            end_ebml_master(pb, tag_target);
        }
    }

    if (mkv->mode != MODE_WEBM) {
        for (i = 0; i < s->nb_chapters; i++) {
            AVChapter *ch = s->chapters[i];

            if (!mkv_check_tag(ch->metadata, MATROSKA_ID_TAGTARGETS_CHAPTERUID))
                continue;

            ret = mkv_write_tag(s, ch->metadata, MATROSKA_ID_TAGTARGETS_CHAPTERUID, ch->id + mkv->chapter_id_offset, &mkv->tags);
            if (ret < 0)
                return ret;
        }
    }

    if (mkv->have_attachments && mkv->mode != MODE_WEBM) {
        for (i = 0; i < mkv->attachments->num_entries; i++) {
            mkv_attachment *attachment = &mkv->attachments->entries[i];
            AVStream *st = s->streams[attachment->stream_idx];

            if (!mkv_check_tag(st->metadata, MATROSKA_ID_TAGTARGETS_ATTACHUID))
                continue;

            ret = mkv_write_tag(s, st->metadata, MATROSKA_ID_TAGTARGETS_ATTACHUID, attachment->fileuid, &mkv->tags);
            if (ret < 0)
                return ret;
        }
    }

    if (mkv->tags.pos) {
        if ((s->pb->seekable & AVIO_SEEKABLE_NORMAL) && !mkv->is_live)
            end_ebml_master_crc32_preliminary(s->pb, &mkv->tags_bc, mkv, mkv->tags);
        else
            end_ebml_master_crc32(s->pb, &mkv->tags_bc, mkv, mkv->tags);
    }
    return 0;
}