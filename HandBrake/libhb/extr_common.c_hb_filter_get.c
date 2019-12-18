#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  hb_filter_object_t ;

/* Variables and functions */
#define  HB_FILTER_AVFILTER 149 
#define  HB_FILTER_CHROMA_SMOOTH 148 
#define  HB_FILTER_COLORSPACE 147 
#define  HB_FILTER_COMB_DETECT 146 
#define  HB_FILTER_CROP_SCALE 145 
#define  HB_FILTER_DEBLOCK 144 
#define  HB_FILTER_DECOMB 143 
#define  HB_FILTER_DEINTERLACE 142 
#define  HB_FILTER_DENOISE 141 
#define  HB_FILTER_DETELECINE 140 
#define  HB_FILTER_GRAYSCALE 139 
#define  HB_FILTER_LAPSHARP 138 
#define  HB_FILTER_MT_FRAME 137 
#define  HB_FILTER_NLMEANS 136 
#define  HB_FILTER_PAD 135 
#define  HB_FILTER_QSV 134 
#define  HB_FILTER_QSV_POST 133 
#define  HB_FILTER_QSV_PRE 132 
#define  HB_FILTER_RENDER_SUB 131 
#define  HB_FILTER_ROTATE 130 
#define  HB_FILTER_UNSHARP 129 
#define  HB_FILTER_VFR 128 
 int /*<<< orphan*/  hb_filter_avfilter ; 
 int /*<<< orphan*/  hb_filter_chroma_smooth ; 
 int /*<<< orphan*/  hb_filter_colorspace ; 
 int /*<<< orphan*/  hb_filter_comb_detect ; 
 int /*<<< orphan*/  hb_filter_crop_scale ; 
 int /*<<< orphan*/  hb_filter_deblock ; 
 int /*<<< orphan*/  hb_filter_decomb ; 
 int /*<<< orphan*/  hb_filter_deinterlace ; 
 int /*<<< orphan*/  hb_filter_denoise ; 
 int /*<<< orphan*/  hb_filter_detelecine ; 
 int /*<<< orphan*/  hb_filter_grayscale ; 
 int /*<<< orphan*/  hb_filter_lapsharp ; 
 int /*<<< orphan*/  hb_filter_mt_frame ; 
 int /*<<< orphan*/  hb_filter_nlmeans ; 
 int /*<<< orphan*/  hb_filter_pad ; 
 int /*<<< orphan*/  hb_filter_qsv ; 
 int /*<<< orphan*/  hb_filter_qsv_post ; 
 int /*<<< orphan*/  hb_filter_qsv_pre ; 
 int /*<<< orphan*/  hb_filter_render_sub ; 
 int /*<<< orphan*/  hb_filter_rotate ; 
 int /*<<< orphan*/  hb_filter_unsharp ; 
 int /*<<< orphan*/  hb_filter_vfr ; 

hb_filter_object_t * hb_filter_get( int filter_id )
{
    hb_filter_object_t * filter;
    switch( filter_id )
    {
        case HB_FILTER_DETELECINE:
            filter = &hb_filter_detelecine;
            break;

        case HB_FILTER_COMB_DETECT:
            filter = &hb_filter_comb_detect;
            break;

        case HB_FILTER_DECOMB:
            filter = &hb_filter_decomb;
            break;

        case HB_FILTER_DEINTERLACE:
            filter = &hb_filter_deinterlace;
            break;

        case HB_FILTER_COLORSPACE:
            filter = &hb_filter_colorspace;
            break;

        case HB_FILTER_VFR:
            filter = &hb_filter_vfr;
            break;

        case HB_FILTER_DEBLOCK:
            filter = &hb_filter_deblock;
            break;

        case HB_FILTER_DENOISE:
            filter = &hb_filter_denoise;
            break;

        case HB_FILTER_NLMEANS:
            filter = &hb_filter_nlmeans;
            break;

        case HB_FILTER_CHROMA_SMOOTH:
            filter = &hb_filter_chroma_smooth;
            break;

        case HB_FILTER_RENDER_SUB:
            filter = &hb_filter_render_sub;
            break;

        case HB_FILTER_CROP_SCALE:
            filter = &hb_filter_crop_scale;
            break;

        case HB_FILTER_LAPSHARP:
            filter = &hb_filter_lapsharp;
            break;

        case HB_FILTER_UNSHARP:
            filter = &hb_filter_unsharp;
            break;

        case HB_FILTER_AVFILTER:
            filter = &hb_filter_avfilter;
            break;

        case HB_FILTER_PAD:
            filter = &hb_filter_pad;
            break;

        case HB_FILTER_ROTATE:
            filter = &hb_filter_rotate;
            break;

        case HB_FILTER_GRAYSCALE:
            filter = &hb_filter_grayscale;
            break;

#if HB_PROJECT_FEATURE_QSV
        case HB_FILTER_QSV:
            filter = &hb_filter_qsv;
            break;

        case HB_FILTER_QSV_PRE:
            filter = &hb_filter_qsv_pre;
            break;

        case HB_FILTER_QSV_POST:
            filter = &hb_filter_qsv_post;
            break;
#endif

        case HB_FILTER_MT_FRAME:
            filter = &hb_filter_mt_frame;
            break;

        default:
            filter = NULL;
            break;
    }
    return filter;
}