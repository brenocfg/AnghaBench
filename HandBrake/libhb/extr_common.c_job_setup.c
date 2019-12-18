#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uiGeo ;
struct TYPE_19__ {int /*<<< orphan*/  par; scalar_t__ height; scalar_t__ width; } ;
struct TYPE_17__ {int video_decode_support; int /*<<< orphan*/  metadata; int /*<<< orphan*/  list_attachment; int /*<<< orphan*/  color_range; int /*<<< orphan*/  color_matrix; int /*<<< orphan*/  color_transfer; int /*<<< orphan*/  color_prim; int /*<<< orphan*/  vrate; int /*<<< orphan*/  crop; TYPE_6__ geometry; int /*<<< orphan*/  list_chapter; } ;
typedef  TYPE_4__ hb_title_t ;
struct TYPE_15__ {scalar_t__ is_init_done; } ;
struct TYPE_16__ {int decode; int /*<<< orphan*/  async_depth; TYPE_2__ enc_info; } ;
struct TYPE_18__ {int chapter_start; int vbitrate; TYPE_3__ qsv; int /*<<< orphan*/  metadata; int /*<<< orphan*/  list_attachment; void* list_filter; void* list_subtitle; void* list_audio; int /*<<< orphan*/  mux; int /*<<< orphan*/  color_matrix_override; int /*<<< orphan*/  color_transfer_override; int /*<<< orphan*/  color_prim_override; int /*<<< orphan*/  color_range; int /*<<< orphan*/  color_matrix; int /*<<< orphan*/  color_transfer; int /*<<< orphan*/  color_prim; int /*<<< orphan*/  pix_fmt; int /*<<< orphan*/  vrate; int /*<<< orphan*/  pass_id; scalar_t__ twopass; int /*<<< orphan*/  vquality; int /*<<< orphan*/  vcodec; int /*<<< orphan*/  par; scalar_t__ height; scalar_t__ width; scalar_t__* crop; int /*<<< orphan*/  list_chapter; int /*<<< orphan*/  chapter_end; TYPE_4__* title; } ;
typedef  TYPE_5__ hb_job_t ;
typedef  TYPE_6__ hb_geometry_t ;
struct TYPE_14__ {scalar_t__ height; scalar_t__ width; } ;
struct TYPE_20__ {int /*<<< orphan*/  keep; int /*<<< orphan*/  mode; scalar_t__* crop; TYPE_1__ geometry; } ;
typedef  TYPE_7__ hb_geometry_settings_t ;

/* Variables and functions */
 int /*<<< orphan*/  AV_PIX_FMT_YUV420P ; 
 int /*<<< orphan*/  HB_ANAMORPHIC_NONE ; 
 int /*<<< orphan*/  HB_COLR_MAT_UNDEF ; 
 int /*<<< orphan*/  HB_COLR_PRI_UNDEF ; 
 int /*<<< orphan*/  HB_COLR_TRA_UNDEF ; 
 int HB_DECODE_SUPPORT_QSV ; 
 int /*<<< orphan*/  HB_INVALID_VIDEO_QUALITY ; 
 int /*<<< orphan*/  HB_KEEP_DISPLAY_ASPECT ; 
 int /*<<< orphan*/  HB_MUX_MP4 ; 
 int /*<<< orphan*/  HB_PASS_ENCODE ; 
 int /*<<< orphan*/  HB_QSV_ASYNC_DEPTH_DEFAULT ; 
 int /*<<< orphan*/  HB_VCODEC_FFMPEG_MPEG4 ; 
 int /*<<< orphan*/  hb_attachment_list_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_chapter_list_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_list_count (int /*<<< orphan*/ ) ; 
 void* hb_list_init () ; 
 int /*<<< orphan*/  hb_metadata_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_set_anamorphic_size2 (TYPE_6__*,TYPE_7__*,TYPE_6__*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void job_setup(hb_job_t * job, hb_title_t * title)
{
    if ( job == NULL || title == NULL )
        return;

    job->title = title;

    /* Set defaults settings */
    job->chapter_start = 1;
    job->chapter_end   = hb_list_count( title->list_chapter );
    job->list_chapter = hb_chapter_list_copy( title->list_chapter );

    /* Autocrop by default. Gnark gnark */
    memcpy( job->crop, title->crop, 4 * sizeof( int ) );


    hb_geometry_t resultGeo, srcGeo;
    hb_geometry_settings_t uiGeo;

    srcGeo = title->geometry;

    memset(&uiGeo, 0, sizeof(uiGeo));
    memcpy(uiGeo.crop, title->crop, 4 * sizeof( int ));
    uiGeo.geometry.width = srcGeo.width - uiGeo.crop[2] - uiGeo.crop[3];
    uiGeo.geometry.height = srcGeo.height - uiGeo.crop[0] - uiGeo.crop[1];
    uiGeo.mode = HB_ANAMORPHIC_NONE;
    uiGeo.keep = HB_KEEP_DISPLAY_ASPECT;

    hb_set_anamorphic_size2(&srcGeo, &uiGeo, &resultGeo);
    job->width = resultGeo.width;
    job->height = resultGeo.height;
    job->par = resultGeo.par;

    job->vcodec     = HB_VCODEC_FFMPEG_MPEG4;
    job->vquality   = HB_INVALID_VIDEO_QUALITY;
    job->vbitrate   = 1000;
    job->twopass    = 0;
    job->pass_id    = HB_PASS_ENCODE;
    job->vrate      = title->vrate;

    job->pix_fmt        = AV_PIX_FMT_YUV420P;
    job->color_prim     = title->color_prim;
    job->color_transfer = title->color_transfer;
    job->color_matrix   = title->color_matrix;
    job->color_range    = title->color_range;
    job->color_prim_override     = HB_COLR_PRI_UNDEF;
    job->color_transfer_override = HB_COLR_TRA_UNDEF;
    job->color_matrix_override   = HB_COLR_MAT_UNDEF;

    job->mux = HB_MUX_MP4;

    job->list_audio = hb_list_init();
    job->list_subtitle = hb_list_init();
    job->list_filter = hb_list_init();

    job->list_attachment = hb_attachment_list_copy( title->list_attachment );
    job->metadata = hb_metadata_copy( title->metadata );

#if HB_PROJECT_FEATURE_QSV
    job->qsv.enc_info.is_init_done = 0;
    job->qsv.async_depth           = HB_QSV_ASYNC_DEPTH_DEFAULT;
    job->qsv.decode                = !!(title->video_decode_support &
                                        HB_DECODE_SUPPORT_QSV);
#endif
}