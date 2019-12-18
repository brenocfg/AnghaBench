#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_7__ {int size; scalar_t__ data; } ;
struct TYPE_5__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
struct TYPE_6__ {int self_size; TYPE_1__ qoffset; int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
typedef  TYPE_2__ AVRegionOfInterest ;
typedef  TYPE_3__ AVFrameSideData ;
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void dump_roi(AVFilterContext *ctx, AVFrameSideData *sd)
{
    int nb_rois;
    const AVRegionOfInterest *roi;
    uint32_t roi_size;

    roi = (const AVRegionOfInterest *)sd->data;
    roi_size = roi->self_size;
    if (!roi_size || sd->size % roi_size != 0) {
        av_log(ctx, AV_LOG_ERROR, "Invalid AVRegionOfInterest.self_size.");
        return;
    }
    nb_rois = sd->size / roi_size;

    av_log(ctx, AV_LOG_INFO, "Regions Of Interest(RoI) information: ");
    for (int i = 0; i < nb_rois; i++) {
        roi = (const AVRegionOfInterest *)(sd->data + roi_size * i);
        av_log(ctx, AV_LOG_INFO, "index: %d, region: (%d, %d)/(%d, %d), qp offset: %d/%d.\n",
               i, roi->left, roi->top, roi->right, roi->bottom, roi->qoffset.num, roi->qoffset.den);
    }
}