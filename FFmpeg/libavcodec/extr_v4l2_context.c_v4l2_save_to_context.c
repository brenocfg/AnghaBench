#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct v4l2_format_update {int /*<<< orphan*/  v4l2_fmt; scalar_t__ update_v4l2; int /*<<< orphan*/  av_fmt; scalar_t__ update_avfmt; } ;
struct TYPE_11__ {void* sizeimage; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  width; int /*<<< orphan*/  height; } ;
struct TYPE_10__ {TYPE_1__* plane_fmt; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  width; int /*<<< orphan*/  height; } ;
struct TYPE_12__ {TYPE_3__ pix; TYPE_2__ pix_mp; } ;
struct TYPE_13__ {TYPE_4__ fmt; int /*<<< orphan*/  type; } ;
struct TYPE_14__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_5__ format; int /*<<< orphan*/  type; int /*<<< orphan*/  av_pix_fmt; } ;
typedef  TYPE_6__ V4L2Context ;
struct TYPE_9__ {void* sizeimage; } ;

/* Variables and functions */
 scalar_t__ V4L2_TYPE_IS_MULTIPLANAR (int /*<<< orphan*/ ) ; 
 void* v4l2_get_framesize_compressed (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void v4l2_save_to_context(V4L2Context* ctx, struct v4l2_format_update *fmt)
{
    ctx->format.type = ctx->type;

    if (fmt->update_avfmt)
        ctx->av_pix_fmt = fmt->av_fmt;

    if (V4L2_TYPE_IS_MULTIPLANAR(ctx->type)) {
        /* update the sizes to handle the reconfiguration of the capture stream at runtime */
        ctx->format.fmt.pix_mp.height = ctx->height;
        ctx->format.fmt.pix_mp.width = ctx->width;
        if (fmt->update_v4l2) {
            ctx->format.fmt.pix_mp.pixelformat = fmt->v4l2_fmt;

            /* s5p-mfc requires the user to specify a buffer size */
            ctx->format.fmt.pix_mp.plane_fmt[0].sizeimage =
                v4l2_get_framesize_compressed(ctx, ctx->width, ctx->height);
        }
    } else {
        ctx->format.fmt.pix.height = ctx->height;
        ctx->format.fmt.pix.width = ctx->width;
        if (fmt->update_v4l2) {
            ctx->format.fmt.pix.pixelformat = fmt->v4l2_fmt;

            /* s5p-mfc requires the user to specify a buffer size */
            ctx->format.fmt.pix.sizeimage =
                v4l2_get_framesize_compressed(ctx, ctx->width, ctx->height);
        }
    }
}