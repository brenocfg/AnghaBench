#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int version; int /*<<< orphan*/  slice_height; int /*<<< orphan*/  slice_width; int /*<<< orphan*/  slice_y; int /*<<< orphan*/  slice_x; int /*<<< orphan*/  slice_count; int /*<<< orphan*/  packed_at_lsb; int /*<<< orphan*/  bits_per_raw_sample; int /*<<< orphan*/  key_frame_ok; int /*<<< orphan*/  slice_damaged; int /*<<< orphan*/  intra; int /*<<< orphan*/  ec; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  ac; int /*<<< orphan*/  plane_count; int /*<<< orphan*/  transparency; int /*<<< orphan*/  chroma_v_shift; int /*<<< orphan*/  chroma_h_shift; int /*<<< orphan*/  chroma_planes; int /*<<< orphan*/  micro_version; } ;
typedef  TYPE_1__ FFV1Context ;

/* Variables and functions */

__attribute__((used)) static void copy_fields(FFV1Context *fsdst, FFV1Context *fssrc, FFV1Context *fsrc)
{
    fsdst->version             = fsrc->version;
    fsdst->micro_version       = fsrc->micro_version;
    fsdst->chroma_planes       = fsrc->chroma_planes;
    fsdst->chroma_h_shift      = fsrc->chroma_h_shift;
    fsdst->chroma_v_shift      = fsrc->chroma_v_shift;
    fsdst->transparency        = fsrc->transparency;
    fsdst->plane_count         = fsrc->plane_count;
    fsdst->ac                  = fsrc->ac;
    fsdst->colorspace          = fsrc->colorspace;

    fsdst->ec                  = fsrc->ec;
    fsdst->intra               = fsrc->intra;
    fsdst->slice_damaged       = fssrc->slice_damaged;
    fsdst->key_frame_ok        = fsrc->key_frame_ok;

    fsdst->bits_per_raw_sample = fsrc->bits_per_raw_sample;
    fsdst->packed_at_lsb       = fsrc->packed_at_lsb;
    fsdst->slice_count         = fsrc->slice_count;
    if (fsrc->version<3){
        fsdst->slice_x             = fssrc->slice_x;
        fsdst->slice_y             = fssrc->slice_y;
        fsdst->slice_width         = fssrc->slice_width;
        fsdst->slice_height        = fssrc->slice_height;
    }
}