#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct playlist {int id3_found; int id3_changed; int /*<<< orphan*/ * id3_deferred_extra; int /*<<< orphan*/  parent; int /*<<< orphan*/ * id3_initial; TYPE_1__* ctx; scalar_t__ id3_offset; scalar_t__ id3_mpegts_timestamp; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_3__ {int /*<<< orphan*/  metadata; scalar_t__ nb_streams; } ;
typedef  int /*<<< orphan*/  ID3v2ExtraMetaAPIC ;
typedef  int /*<<< orphan*/  ID3v2ExtraMeta ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_dict_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  avpriv_report_missing_feature (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ff_id3v2_free_extra_meta (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ff_id3v2_parse_apic (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ff_id3v2_parse_priv_dict (int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 scalar_t__ id3_has_changed_values (struct playlist*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_id3 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,scalar_t__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void handle_id3(AVIOContext *pb, struct playlist *pls)
{
    AVDictionary *metadata = NULL;
    ID3v2ExtraMetaAPIC *apic = NULL;
    ID3v2ExtraMeta *extra_meta = NULL;
    int64_t timestamp = AV_NOPTS_VALUE;

    parse_id3(pls->ctx, pb, &metadata, &timestamp, &apic, &extra_meta);

    if (timestamp != AV_NOPTS_VALUE) {
        pls->id3_mpegts_timestamp = timestamp;
        pls->id3_offset = 0;
    }

    if (!pls->id3_found) {
        /* initial ID3 tags */
        av_assert0(!pls->id3_deferred_extra);
        pls->id3_found = 1;

        /* get picture attachment and set text metadata */
        if (pls->ctx->nb_streams)
            ff_id3v2_parse_apic(pls->ctx, &extra_meta);
        else
            /* demuxer not yet opened, defer picture attachment */
            pls->id3_deferred_extra = extra_meta;

        ff_id3v2_parse_priv_dict(&metadata, &extra_meta);
        av_dict_copy(&pls->ctx->metadata, metadata, 0);
        pls->id3_initial = metadata;

    } else {
        if (!pls->id3_changed && id3_has_changed_values(pls, metadata, apic)) {
            avpriv_report_missing_feature(pls->parent, "Changing ID3 metadata in HLS audio elementary stream");
            pls->id3_changed = 1;
        }
        av_dict_free(&metadata);
    }

    if (!pls->id3_deferred_extra)
        ff_id3v2_free_extra_meta(&extra_meta);
}