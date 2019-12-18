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
struct TYPE_3__ {int asset_offset; int asset_size; int extension_mask; int core_offset; int core_size; int xbr_offset; int xbr_size; int xxch_offset; int xxch_size; int x96_offset; int x96_size; int lbr_offset; int lbr_size; int xll_offset; int xll_size; } ;
typedef  TYPE_1__ DCAExssAsset ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int DCA_EXSS_CORE ; 
 int DCA_EXSS_LBR ; 
 int DCA_EXSS_X96 ; 
 int DCA_EXSS_XBR ; 
 int DCA_EXSS_XLL ; 
 int DCA_EXSS_XXCH ; 

__attribute__((used)) static int set_exss_offsets(DCAExssAsset *asset)
{
    int offs = asset->asset_offset;
    int size = asset->asset_size;

    if (asset->extension_mask & DCA_EXSS_CORE) {
        asset->core_offset = offs;
        if (asset->core_size > size)
            return AVERROR_INVALIDDATA;
        offs += asset->core_size;
        size -= asset->core_size;
    }

    if (asset->extension_mask & DCA_EXSS_XBR) {
        asset->xbr_offset = offs;
        if (asset->xbr_size > size)
            return AVERROR_INVALIDDATA;
        offs += asset->xbr_size;
        size -= asset->xbr_size;
    }

    if (asset->extension_mask & DCA_EXSS_XXCH) {
        asset->xxch_offset = offs;
        if (asset->xxch_size > size)
            return AVERROR_INVALIDDATA;
        offs += asset->xxch_size;
        size -= asset->xxch_size;
    }

    if (asset->extension_mask & DCA_EXSS_X96) {
        asset->x96_offset = offs;
        if (asset->x96_size > size)
            return AVERROR_INVALIDDATA;
        offs += asset->x96_size;
        size -= asset->x96_size;
    }

    if (asset->extension_mask & DCA_EXSS_LBR) {
        asset->lbr_offset = offs;
        if (asset->lbr_size > size)
            return AVERROR_INVALIDDATA;
        offs += asset->lbr_size;
        size -= asset->lbr_size;
    }

    if (asset->extension_mask & DCA_EXSS_XLL) {
        asset->xll_offset = offs;
        if (asset->xll_size > size)
            return AVERROR_INVALIDDATA;
        offs += asset->xll_size;
        size -= asset->xll_size;
    }

    return 0;
}