#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_11__ {int* cx2; int* cy2; int* cxy; int* tmpc; int post_processing; int /*<<< orphan*/  tff; int /*<<< orphan*/  noise_threshold; int /*<<< orphan*/  maximum_search_distance; int /*<<< orphan*/  erosion_threshold; int /*<<< orphan*/  dilation_threshold; int /*<<< orphan*/  laplacian_threshold; int /*<<< orphan*/  variance_threshold; int /*<<< orphan*/  magnitude_threshold; TYPE_4__** eedi_half; TYPE_2__** eedi_full; } ;
typedef  TYPE_5__ hb_filter_private_t ;
struct TYPE_10__ {TYPE_3__* plane; } ;
struct TYPE_9__ {int height; int /*<<< orphan*/ * data; } ;
struct TYPE_8__ {TYPE_1__* plane; } ;
struct TYPE_7__ {int stride; int height; int width; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 size_t DST2MPF ; 
 size_t DST2PF ; 
 size_t DSTPF ; 
 size_t MSK2PF ; 
 size_t MSKPF ; 
 size_t SRCPF ; 
 size_t TMP2PF ; 
 size_t TMP2PF2 ; 
 size_t TMPPF ; 
 int /*<<< orphan*/  eedi2_bit_blit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  eedi2_build_edge_mask (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  eedi2_calc_derivatives (int /*<<< orphan*/ *,int,int,int,int*,int*,int*) ; 
 int /*<<< orphan*/  eedi2_calc_directions (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  eedi2_dilate_edge_mask (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  eedi2_erode_edge_mask (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  eedi2_expand_dir_map (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  eedi2_expand_dir_map_2x (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  eedi2_fill_gaps_2x (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  eedi2_filter_dir_map (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  eedi2_filter_dir_map_2x (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  eedi2_filter_map (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  eedi2_gaussian_blur1 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  eedi2_gaussian_blur_sqrt2 (int*,int*,int*,int,int,int) ; 
 int /*<<< orphan*/  eedi2_interpolate_lattice (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  eedi2_mark_directions_2x (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  eedi2_post_process (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  eedi2_post_process_corner (int*,int*,int*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eedi2_remove_small_gaps (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  eedi2_upscale_by_2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void eedi2_interpolate_plane( hb_filter_private_t * pv, int plane )
{
    /* We need all these pointers. No, seriously.
       I swear. It's not a joke. They're used.
       All nine of them.                         */
    uint8_t * mskp = pv->eedi_half[MSKPF]->plane[plane].data;
    uint8_t * srcp = pv->eedi_half[SRCPF]->plane[plane].data;
    uint8_t * tmpp = pv->eedi_half[TMPPF]->plane[plane].data;
    uint8_t * dstp = pv->eedi_half[DSTPF]->plane[plane].data;
    uint8_t * dst2p = pv->eedi_full[DST2PF]->plane[plane].data;
    uint8_t * tmp2p2 = pv->eedi_full[TMP2PF2]->plane[plane].data;
    uint8_t * msk2p = pv->eedi_full[MSK2PF]->plane[plane].data;
    uint8_t * tmp2p = pv->eedi_full[TMP2PF]->plane[plane].data;
    uint8_t * dst2mp = pv->eedi_full[DST2MPF]->plane[plane].data;
    int * cx2 = pv->cx2;
    int * cy2 = pv->cy2;
    int * cxy = pv->cxy;
    int * tmpc = pv->tmpc;

    int pitch = pv->eedi_full[0]->plane[plane].stride;
    int height = pv->eedi_full[0]->plane[plane].height;
    int width = pv->eedi_full[0]->plane[plane].width;
    int half_height = pv->eedi_half[0]->plane[plane].height;

    // edge mask
    eedi2_build_edge_mask( mskp, pitch, srcp, pitch,
                     pv->magnitude_threshold, pv->variance_threshold, pv->laplacian_threshold,
                     half_height, width );
    eedi2_erode_edge_mask( mskp, pitch, tmpp, pitch, pv->erosion_threshold, half_height, width );
    eedi2_dilate_edge_mask( tmpp, pitch, mskp, pitch, pv->dilation_threshold, half_height, width );
    eedi2_erode_edge_mask( mskp, pitch, tmpp, pitch, pv->erosion_threshold, half_height, width );
    eedi2_remove_small_gaps( tmpp, pitch, mskp, pitch, half_height, width );

    // direction mask
    eedi2_calc_directions( plane, mskp, pitch, srcp, pitch, tmpp, pitch,
                     pv->maximum_search_distance, pv->noise_threshold,
                     half_height, width );
    eedi2_filter_dir_map( mskp, pitch, tmpp, pitch, dstp, pitch, half_height, width );
    eedi2_expand_dir_map( mskp, pitch, dstp, pitch, tmpp, pitch, half_height, width );
    eedi2_filter_map( mskp, pitch, tmpp, pitch, dstp, pitch, half_height, width );

    // upscale 2x vertically
    eedi2_upscale_by_2( srcp, dst2p, half_height, pitch );
    eedi2_upscale_by_2( dstp, tmp2p2, half_height, pitch );
    eedi2_upscale_by_2( mskp, msk2p, half_height, pitch );

    // upscale the direction mask
    eedi2_mark_directions_2x( msk2p, pitch, tmp2p2, pitch, tmp2p, pitch, pv->tff, height, width );
    eedi2_filter_dir_map_2x( msk2p, pitch, tmp2p, pitch,  dst2mp, pitch, pv->tff, height, width );
    eedi2_expand_dir_map_2x( msk2p, pitch, dst2mp, pitch, tmp2p, pitch, pv->tff, height, width );
    eedi2_fill_gaps_2x( msk2p, pitch, tmp2p, pitch, dst2mp, pitch, pv->tff, height, width );
    eedi2_fill_gaps_2x( msk2p, pitch, dst2mp, pitch, tmp2p, pitch, pv->tff, height, width );

    // interpolate a full-size plane
    eedi2_interpolate_lattice( plane, tmp2p, pitch, dst2p, pitch, tmp2p2, pitch, pv->tff,
                         pv->noise_threshold, height, width );

    if( pv->post_processing == 1 || pv->post_processing == 3 )
    {
        // make sure the edge directions are consistent
        eedi2_bit_blit( tmp2p2, pitch, tmp2p, pitch, width, height );
        eedi2_filter_dir_map_2x( msk2p, pitch, tmp2p, pitch, dst2mp, pitch, pv->tff, height, width );
        eedi2_expand_dir_map_2x( msk2p, pitch, dst2mp, pitch, tmp2p, pitch, pv->tff, height, width );
        eedi2_post_process( tmp2p, pitch, tmp2p2, pitch, dst2p, pitch, pv->tff, height, width );
    }
    if( pv->post_processing == 2 || pv->post_processing == 3 )
    {
        // filter junctions and corners
        eedi2_gaussian_blur1( srcp, pitch, tmpp, pitch, srcp, pitch, half_height, width );
        eedi2_calc_derivatives( srcp, pitch, half_height, width, cx2, cy2, cxy );
        eedi2_gaussian_blur_sqrt2( cx2, tmpc, cx2, pitch, half_height, width);
        eedi2_gaussian_blur_sqrt2( cy2, tmpc, cy2, pitch, half_height, width);
        eedi2_gaussian_blur_sqrt2( cxy, tmpc, cxy, pitch, half_height, width);
        eedi2_post_process_corner( cx2, cy2, cxy, pitch, tmp2p2, pitch, dst2p, pitch, height, width, pv->tff );
    }
}