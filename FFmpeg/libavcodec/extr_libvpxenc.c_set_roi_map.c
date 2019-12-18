#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int* delta_q; int rows; int cols; int* roi_map; } ;
typedef  TYPE_2__ vpx_roi_map_t ;
typedef  int uint32_t ;
struct TYPE_11__ {int size; scalar_t__ data; } ;
struct TYPE_8__ {float den; float num; } ;
struct TYPE_10__ {int self_size; int top; int bottom; int left; int right; TYPE_1__ qoffset; } ;
typedef  TYPE_3__ AVRegionOfInterest ;
typedef  TYPE_4__ AVFrameSideData ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int MAX_DELTA_Q ; 
 int av_clip (int,int,int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int* av_mallocz_array (int,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int set_roi_map(AVCodecContext *avctx, const AVFrameSideData *sd, int frame_width, int frame_height,
                       vpx_roi_map_t *roi_map, int block_size, int segment_cnt)
{
    /**
     * range of vpx_roi_map_t.delta_q[i] is [-63, 63]
     */
#define MAX_DELTA_Q 63

    const AVRegionOfInterest *roi = NULL;
    int nb_rois;
    uint32_t self_size;
    int segment_id;

    /* record the mapping from delta_q to "segment id + 1" in segment_mapping[].
     * the range of delta_q is [-MAX_DELTA_Q, MAX_DELTA_Q],
     * and its corresponding array index is [0, 2 * MAX_DELTA_Q],
     * and so the length of the mapping array is 2 * MAX_DELTA_Q + 1.
     * "segment id + 1", so we can say there's no mapping if the value of array element is zero.
     */
    int segment_mapping[2 * MAX_DELTA_Q + 1] = { 0 };

    memset(roi_map, 0, sizeof(*roi_map));

    /* segment id 0 in roi_map is reserved for the areas not covered by AVRegionOfInterest.
     * segment id 0 in roi_map is also for the areas with AVRegionOfInterest.qoffset near 0.
     * (delta_q of segment id 0 is 0).
     */
    segment_mapping[MAX_DELTA_Q] = 1;
    segment_id = 1;

    roi = (const AVRegionOfInterest*)sd->data;
    self_size = roi->self_size;
    if (!self_size || sd->size % self_size) {
        av_log(avctx, AV_LOG_ERROR, "Invalid AVRegionOfInterest.self_size.\n");
        return AVERROR(EINVAL);
    }
    nb_rois = sd->size / self_size;

    /* This list must be iterated from zero because regions are
     * defined in order of decreasing importance. So discard less
     * important areas if they exceed the segment count.
     */
    for (int i = 0; i < nb_rois; i++) {
        int delta_q;
        int mapping_index;

        roi = (const AVRegionOfInterest*)(sd->data + self_size * i);
        if (!roi->qoffset.den) {
            av_log(avctx, AV_LOG_ERROR, "AVRegionOfInterest.qoffset.den must not be zero.\n");
            return AVERROR(EINVAL);
        }

        delta_q = (int)(roi->qoffset.num * 1.0f / roi->qoffset.den * MAX_DELTA_Q);
        delta_q = av_clip(delta_q, -MAX_DELTA_Q, MAX_DELTA_Q);

        mapping_index = delta_q + MAX_DELTA_Q;
        if (!segment_mapping[mapping_index]) {
            if (segment_id == segment_cnt) {
                av_log(avctx, AV_LOG_WARNING,
                       "ROI only supports %d segments (and segment 0 is reserved for non-ROIs), skipping the left ones.\n",
                       segment_cnt);
                break;
            }

            segment_mapping[mapping_index] = segment_id + 1;
            roi_map->delta_q[segment_id] = delta_q;
            segment_id++;
        }
    }

    roi_map->rows = (frame_height + block_size - 1) / block_size;
    roi_map->cols = (frame_width  + block_size - 1) / block_size;
    roi_map->roi_map = av_mallocz_array(roi_map->rows * roi_map->cols, sizeof(*roi_map->roi_map));
    if (!roi_map->roi_map) {
        av_log(avctx, AV_LOG_ERROR, "roi_map alloc failed.\n");
        return AVERROR(ENOMEM);
    }

    /* This list must be iterated in reverse, so for the case that
     * two regions are overlapping, the more important area takes effect.
     */
    for (int i = nb_rois - 1; i >= 0; i--) {
        int delta_q;
        int mapping_value;
        int starty, endy, startx, endx;

        roi = (const AVRegionOfInterest*)(sd->data + self_size * i);

        starty = av_clip(roi->top / block_size, 0, roi_map->rows);
        endy   = av_clip((roi->bottom + block_size - 1) / block_size, 0, roi_map->rows);
        startx = av_clip(roi->left / block_size, 0, roi_map->cols);
        endx   = av_clip((roi->right + block_size - 1) / block_size, 0, roi_map->cols);

        delta_q = (int)(roi->qoffset.num * 1.0f / roi->qoffset.den * MAX_DELTA_Q);
        delta_q = av_clip(delta_q, -MAX_DELTA_Q, MAX_DELTA_Q);

        mapping_value = segment_mapping[delta_q + MAX_DELTA_Q];
        if (mapping_value) {
            for (int y = starty; y < endy; y++)
                for (int x = startx; x < endx; x++)
                    roi_map->roi_map[x + y * roi_map->cols] = mapping_value - 1;
        }
    }

    return 0;
}