#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_13__ {int sws_width; int sws_height; int* crop; int /*<<< orphan*/ * sws; } ;
typedef  TYPE_2__ hb_filter_private_t ;
struct TYPE_12__ {double window_width; double window_height; int width; int height; double x; double y; int /*<<< orphan*/  fmt; } ;
struct TYPE_14__ {TYPE_1__ f; } ;
typedef  TYPE_3__ hb_buffer_t ;

/* Variables and functions */
 double ABS (double) ; 
 int /*<<< orphan*/  AV_PIX_FMT_YUVA420P ; 
 int SWS_ACCURATE_RND ; 
 int /*<<< orphan*/  SWS_CS_DEFAULT ; 
 int SWS_LANCZOS ; 
 TYPE_3__* hb_buffer_dup (TYPE_3__*) ; 
 TYPE_3__* hb_frame_buffer_init (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  hb_picture_fill (int /*<<< orphan*/ **,int*,TYPE_3__*) ; 
 int /*<<< orphan*/ * hb_sws_get_context (double,double,int /*<<< orphan*/ ,double,double,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sws_freeContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sws_scale (int /*<<< orphan*/ *,int /*<<< orphan*/  const* const*,int*,int /*<<< orphan*/ ,double,int /*<<< orphan*/ **,int*) ; 

__attribute__((used)) static hb_buffer_t * ScaleSubtitle(hb_filter_private_t *pv,
                                   hb_buffer_t *sub, hb_buffer_t *buf)
{
    hb_buffer_t * scaled;
    double xfactor = 1., yfactor = 1.;

    // Do we need to rescale subtitles?
    if (sub->f.window_width > 0 && sub->f.window_height > 0)
    {

        // TODO: Factor aspect ratio
        // For now, assume subtitle and video PAR is the same.
        xfactor     = (double)buf->f.width  / sub->f.window_width;
        yfactor     = (double)buf->f.height / sub->f.window_height;
        // The video may have been cropped.  This will make xfactor != yfactor
        // even though video and subtitles are the same PAR.  So use the
        // larger of as the scale factor.
        if (xfactor > yfactor)
        {
            yfactor = xfactor;
        }
        else
        {
            xfactor = yfactor;
        }
    }
    if (ABS(xfactor - 1) > 0.01 || ABS(yfactor - 1) > 0.01)
    {
        uint8_t * in_data[4], * out_data[4];
        int       in_stride[4], out_stride[4];
        int       width, height;

        width       = sub->f.width  * xfactor;
        height      = sub->f.height * yfactor;
        // Note that subtitle frame buffer is YUVA420P, not YUV420P, it has alpha
        scaled      = hb_frame_buffer_init(AV_PIX_FMT_YUVA420P, width, height);
        if (scaled == NULL)
            return NULL;

        scaled->f.x = sub->f.x * xfactor;
        scaled->f.y = sub->f.y * yfactor;

        hb_picture_fill(in_data,  in_stride,  sub);
        hb_picture_fill(out_data, out_stride, scaled);

        if (pv->sws        == NULL   ||
            pv->sws_width  != width  ||
            pv->sws_height != height)
        {
            if (pv->sws!= NULL)
                sws_freeContext(pv->sws);
            pv->sws = hb_sws_get_context(
                                sub->f.width, sub->f.height, sub->f.fmt,
                                scaled->f.width, scaled->f.height, sub->f.fmt,
                                SWS_LANCZOS|SWS_ACCURATE_RND, SWS_CS_DEFAULT);
            pv->sws_width   = width;
            pv->sws_height  = height;
        }
        sws_scale(pv->sws, (const uint8_t* const *)in_data, in_stride,
                  0, sub->f.height, out_data, out_stride);
    }
    else
    {
        scaled = hb_buffer_dup(sub);
    }

    int top, left, margin_top, margin_percent;

    /*
     * Percent of height of picture that form a margin that subtitles
     * should not be displayed within.
     */
    margin_percent = 2;

    /*
     * If necessary, move the subtitle so it is not in a cropped zone.
     * When it won't fit, we center it so we lose as much on both ends.
     * Otherwise we try to leave a 20px or 2% margin around it.
     */
    margin_top = ( ( buf->f.height - pv->crop[0] - pv->crop[1] ) *
                   margin_percent ) / 100;

    if( margin_top > 20 )
    {
        /*
         * A maximum margin of 20px regardless of height of the picture.
         */
        margin_top = 20;
    }

    if( scaled->f.height > buf->f.height - pv->crop[0] - pv->crop[1] -
        ( margin_top * 2 ) )
    {
        /*
         * The subtitle won't fit in the cropped zone, so center
         * it vertically so we fit in as much as we can.
         */
        top = pv->crop[0] + ( buf->f.height - pv->crop[0] -
                                      pv->crop[1] - scaled->f.height ) / 2;
    }
    else if( scaled->f.y < pv->crop[0] + margin_top )
    {
        /*
         * The subtitle fits in the cropped zone, but is currently positioned
         * within our top margin, so move it outside of our margin.
         */
        top = pv->crop[0] + margin_top;
    }
    else if( scaled->f.y > buf->f.height - pv->crop[1] - margin_top - scaled->f.height )
    {
        /*
         * The subtitle fits in the cropped zone, and is not within the top
         * margin but is within the bottom margin, so move it to be above
         * the margin.
         */
        top = buf->f.height - pv->crop[1] - margin_top - scaled->f.height;
    }
    else
    {
        /*
         * The subtitle is fine where it is.
         */
        top = scaled->f.y;
    }

    if( scaled->f.width > buf->f.width - pv->crop[2] - pv->crop[3] - 40 )
        left = pv->crop[2] + ( buf->f.width - pv->crop[2] -
                pv->crop[3] - scaled->f.width ) / 2;
    else if( scaled->f.x < pv->crop[2] + 20 )
        left = pv->crop[2] + 20;
    else if( scaled->f.x > buf->f.width - pv->crop[3] - 20 - scaled->f.width )
        left = buf->f.width - pv->crop[3] - 20 - scaled->f.width;
    else
        left = scaled->f.x;

    scaled->f.x = left;
    scaled->f.y = top;

    return scaled;
}