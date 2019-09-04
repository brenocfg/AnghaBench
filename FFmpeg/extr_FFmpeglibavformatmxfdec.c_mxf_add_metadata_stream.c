#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int /*<<< orphan*/  metadata; int /*<<< orphan*/  id; TYPE_1__* codecpar; } ;
struct TYPE_22__ {int /*<<< orphan*/  id; } ;
struct TYPE_21__ {int /*<<< orphan*/  fc; } ;
struct TYPE_20__ {int /*<<< orphan*/  package_uid; int /*<<< orphan*/  package_ul; } ;
struct TYPE_19__ {int /*<<< orphan*/  source_package_uid; int /*<<< orphan*/  source_package_ul; } ;
struct TYPE_18__ {TYPE_2__* sequence; scalar_t__* name; int /*<<< orphan*/  track_id; } ;
struct TYPE_17__ {int structural_components_count; int /*<<< orphan*/  data_definition_ul; int /*<<< orphan*/ * structural_components_refs; } ;
struct TYPE_16__ {int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_3__ MXFTrack ;
typedef  TYPE_4__ MXFStructuralComponent ;
typedef  TYPE_5__ MXFPackage ;
typedef  TYPE_6__ MXFContext ;
typedef  TYPE_7__ MXFCodecUL ;
typedef  TYPE_8__ AVStream ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_DATA ; 
 int /*<<< orphan*/  AV_CODEC_ID_NONE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,char*,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__* av_get_media_type_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_8__* avformat_new_stream (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_mxf_data_definition_uls ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mxf_add_umid_metadata (int /*<<< orphan*/ *,char*,TYPE_5__*) ; 
 TYPE_7__* mxf_get_codec_ul (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_4__* mxf_resolve_sourceclip (TYPE_6__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mxf_add_metadata_stream(MXFContext *mxf, MXFTrack *track)
{
    MXFStructuralComponent *component = NULL;
    const MXFCodecUL *codec_ul = NULL;
    MXFPackage tmp_package;
    AVStream *st;
    int j;

    for (j = 0; j < track->sequence->structural_components_count; j++) {
        component = mxf_resolve_sourceclip(mxf, &track->sequence->structural_components_refs[j]);
        if (!component)
            continue;
        break;
    }
    if (!component)
        return 0;

    st = avformat_new_stream(mxf->fc, NULL);
    if (!st) {
        av_log(mxf->fc, AV_LOG_ERROR, "could not allocate metadata stream\n");
        return AVERROR(ENOMEM);
    }

    st->codecpar->codec_type = AVMEDIA_TYPE_DATA;
    st->codecpar->codec_id = AV_CODEC_ID_NONE;
    st->id = track->track_id;

    memcpy(&tmp_package.package_ul, component->source_package_ul, 16);
    memcpy(&tmp_package.package_uid, component->source_package_uid, 16);
    mxf_add_umid_metadata(&st->metadata, "file_package_umid", &tmp_package);
    if (track->name && track->name[0])
        av_dict_set(&st->metadata, "track_name", track->name, 0);

    codec_ul = mxf_get_codec_ul(ff_mxf_data_definition_uls, &track->sequence->data_definition_ul);
    av_dict_set(&st->metadata, "data_type", av_get_media_type_string(codec_ul->id), 0);
    return 0;
}