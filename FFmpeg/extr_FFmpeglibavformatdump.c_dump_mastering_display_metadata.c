#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  max_luminance; int /*<<< orphan*/  min_luminance; int /*<<< orphan*/ * white_point; int /*<<< orphan*/ ** display_primaries; int /*<<< orphan*/  has_luminance; int /*<<< orphan*/  has_primaries; } ;
struct TYPE_4__ {scalar_t__ data; } ;
typedef  TYPE_1__ AVPacketSideData ;
typedef  TYPE_2__ AVMasteringDisplayMetadata ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_q2d (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dump_mastering_display_metadata(void *ctx, AVPacketSideData* sd) {
    AVMasteringDisplayMetadata* metadata = (AVMasteringDisplayMetadata*)sd->data;
    av_log(ctx, AV_LOG_INFO, "Mastering Display Metadata, "
           "has_primaries:%d has_luminance:%d "
           "r(%5.4f,%5.4f) g(%5.4f,%5.4f) b(%5.4f %5.4f) wp(%5.4f, %5.4f) "
           "min_luminance=%f, max_luminance=%f",
           metadata->has_primaries, metadata->has_luminance,
           av_q2d(metadata->display_primaries[0][0]),
           av_q2d(metadata->display_primaries[0][1]),
           av_q2d(metadata->display_primaries[1][0]),
           av_q2d(metadata->display_primaries[1][1]),
           av_q2d(metadata->display_primaries[2][0]),
           av_q2d(metadata->display_primaries[2][1]),
           av_q2d(metadata->white_point[0]), av_q2d(metadata->white_point[1]),
           av_q2d(metadata->min_luminance), av_q2d(metadata->max_luminance));
}