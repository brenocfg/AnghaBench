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
struct TYPE_5__ {TYPE_1__* priv_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  extradata_parsed; int /*<<< orphan*/  new_idr; scalar_t__ idr_pps_seen; scalar_t__ idr_sps_seen; } ;
typedef  TYPE_1__ H264BSFContext ;
typedef  TYPE_2__ AVBSFContext ;

/* Variables and functions */

__attribute__((used)) static void h264_mp4toannexb_flush(AVBSFContext *ctx)
{
    H264BSFContext *s = ctx->priv_data;

    s->idr_sps_seen = 0;
    s->idr_pps_seen = 0;
    s->new_idr      = s->extradata_parsed;
}