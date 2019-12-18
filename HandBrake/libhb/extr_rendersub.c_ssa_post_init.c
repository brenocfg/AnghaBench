#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hb_list_t ;
struct TYPE_13__ {double den; scalar_t__ num; } ;
struct TYPE_14__ {int* crop; TYPE_3__ par; TYPE_2__* title; int /*<<< orphan*/ * list_attachment; } ;
typedef  TYPE_4__ hb_job_t ;
struct TYPE_15__ {int /*<<< orphan*/  renderer; int /*<<< orphan*/  ssaTrack; int /*<<< orphan*/  ssa; } ;
typedef  TYPE_5__ hb_filter_private_t ;
struct TYPE_16__ {TYPE_5__* private_data; } ;
typedef  TYPE_6__ hb_filter_object_t ;
struct TYPE_17__ {scalar_t__ type; int /*<<< orphan*/  size; int /*<<< orphan*/  data; int /*<<< orphan*/  name; } ;
typedef  TYPE_7__ hb_attachment_t ;
struct TYPE_11__ {int height; int width; } ;
struct TYPE_12__ {TYPE_1__ geometry; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASS_HINTING_LIGHT ; 
 scalar_t__ FONT_OTF_ATTACH ; 
 scalar_t__ FONT_TTF_ATTACH ; 
 int /*<<< orphan*/  ass_add_font (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ass_library_init () ; 
 int /*<<< orphan*/  ass_new_track (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ass_renderer_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ass_set_aspect_ratio (int /*<<< orphan*/ ,int,double) ; 
 int /*<<< orphan*/  ass_set_extract_fonts (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ass_set_font_scale (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  ass_set_fonts (int /*<<< orphan*/ ,char const*,char const*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ass_set_frame_size (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ass_set_hinting (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ass_set_line_spacing (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  ass_set_message_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ass_set_style_overrides (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ass_set_use_margins (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_error (char*) ; 
 int hb_list_count (int /*<<< orphan*/ *) ; 
 TYPE_7__* hb_list_item (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hb_log (char*) ; 
 int /*<<< orphan*/  ssa_log ; 

__attribute__((used)) static int ssa_post_init( hb_filter_object_t * filter, hb_job_t * job )
{
    hb_filter_private_t * pv = filter->private_data;

    pv->ssa = ass_library_init();
    if ( !pv->ssa ) {
        hb_error( "decssasub: libass initialization failed\n" );
        return 1;
    }

    // Redirect libass output to hb_log
    ass_set_message_cb( pv->ssa, ssa_log, NULL );

    // Load embedded fonts
    hb_list_t * list_attachment = job->list_attachment;
    int i;
    for ( i = 0; i < hb_list_count(list_attachment); i++ )
    {
        hb_attachment_t * attachment = hb_list_item( list_attachment, i );

        if ( attachment->type == FONT_TTF_ATTACH ||
             attachment->type == FONT_OTF_ATTACH )
        {
            ass_add_font(
                pv->ssa,
                attachment->name,
                attachment->data,
                attachment->size );
        }
    }

    ass_set_extract_fonts( pv->ssa, 1 );
    ass_set_style_overrides( pv->ssa, NULL );

    pv->renderer = ass_renderer_init( pv->ssa );
    if ( !pv->renderer ) {
        hb_log( "decssasub: renderer initialization failed\n" );
        return 1;
    }

    ass_set_use_margins( pv->renderer, 0 );
    ass_set_hinting( pv->renderer, ASS_HINTING_LIGHT ); // VLC 1.0.4 uses this
    ass_set_font_scale( pv->renderer, 1.0 );
    ass_set_line_spacing( pv->renderer, 1.0 );

    // Setup default font family
    //
    // SSA v4.00 requires that "Arial" be the default font
    const char *font = NULL;
    const char *family = "Arial";
    // NOTE: This can sometimes block for several *seconds*.
    //       It seems that process_fontdata() for some embedded fonts is slow.
    ass_set_fonts( pv->renderer, font, family, /*haveFontConfig=*/1, NULL, 1 );

    // Setup track state
    pv->ssaTrack = ass_new_track( pv->ssa );
    if ( !pv->ssaTrack ) {
        hb_log( "decssasub: ssa track initialization failed\n" );
        return 1;
    }

    int height = job->title->geometry.height - job->crop[0] - job->crop[1];
    int width = job->title->geometry.width - job->crop[2] - job->crop[3];
    ass_set_frame_size( pv->renderer, width, height);

    double par = (double)job->par.num / job->par.den;
    ass_set_aspect_ratio( pv->renderer, 1, par );

    return 0;
}