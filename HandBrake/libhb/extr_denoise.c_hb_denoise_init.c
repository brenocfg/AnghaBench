#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct hb_filter_private_s {int dummy; } ;
struct TYPE_5__ {void* output; int /*<<< orphan*/ * hqdn3d_coef; void* input; } ;
typedef  TYPE_1__ hb_filter_private_t ;
struct TYPE_6__ {int /*<<< orphan*/  settings; TYPE_1__* private_data; } ;
typedef  TYPE_2__ hb_filter_object_t ;
typedef  void* hb_filter_init_t ;

/* Variables and functions */
 double HQDN3D_SPATIAL_CHROMA_DEFAULT ; 
 double HQDN3D_SPATIAL_LUMA_DEFAULT ; 
 double HQDN3D_TEMPORAL_LUMA_DEFAULT ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  hb_dict_extract_double (double*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hqdn3d_precalc_coef (int /*<<< orphan*/ ,double) ; 

__attribute__((used)) static int hb_denoise_init( hb_filter_object_t * filter,
                            hb_filter_init_t * init )
{
    filter->private_data = calloc( sizeof(struct hb_filter_private_s), 1 );
    hb_filter_private_t * pv = filter->private_data;

    double spatial_luma, spatial_chroma_b, spatial_chroma_r;
    double temporal_luma, temporal_chroma_b, temporal_chroma_r;

    pv->input = *init;
    if (!hb_dict_extract_double(&spatial_luma, filter->settings, "y-spatial"))
    {
        spatial_luma      = HQDN3D_SPATIAL_LUMA_DEFAULT;
    }
    if (!hb_dict_extract_double(&spatial_chroma_b, filter->settings, "cb-spatial"))
    {
        spatial_chroma_b  = HQDN3D_SPATIAL_CHROMA_DEFAULT *
                            spatial_luma / HQDN3D_SPATIAL_LUMA_DEFAULT;
    }
    if (!hb_dict_extract_double(&spatial_chroma_r, filter->settings, "cr-spatial"))
    {
        spatial_chroma_r  = spatial_chroma_b;
    }
    if (!hb_dict_extract_double(&temporal_luma, filter->settings, "y-temporal"))
    {
        temporal_luma     = HQDN3D_TEMPORAL_LUMA_DEFAULT *
                            spatial_luma / HQDN3D_SPATIAL_LUMA_DEFAULT;
    }
    if (!hb_dict_extract_double(&temporal_chroma_b, filter->settings, "cb-temporal"))
    {
        temporal_chroma_b = temporal_luma * spatial_chroma_b / spatial_luma;
    }
    if (!hb_dict_extract_double(&temporal_chroma_r, filter->settings, "cr-temporal"))
    {
        temporal_chroma_r = temporal_chroma_b;
    }

    hqdn3d_precalc_coef( pv->hqdn3d_coef[0], spatial_luma );
    hqdn3d_precalc_coef( pv->hqdn3d_coef[1], temporal_luma );
    hqdn3d_precalc_coef( pv->hqdn3d_coef[2], spatial_chroma_b );
    hqdn3d_precalc_coef( pv->hqdn3d_coef[3], temporal_chroma_b );
    hqdn3d_precalc_coef( pv->hqdn3d_coef[4], spatial_chroma_r );
    hqdn3d_precalc_coef( pv->hqdn3d_coef[5], temporal_chroma_r );

    pv->output = *init;

    return 0;
}