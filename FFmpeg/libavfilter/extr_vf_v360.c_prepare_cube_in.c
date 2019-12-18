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
struct TYPE_5__ {char* in_forder; int* in_cubemap_face_order; char* in_frot; int* in_cubemap_face_rotation; } ;
typedef  TYPE_1__ V360Context ;
struct TYPE_6__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int NB_FACES ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 int get_direction (char const) ; 
 int get_rotation (char const) ; 

__attribute__((used)) static int prepare_cube_in(AVFilterContext *ctx)
{
    V360Context *s = ctx->priv;

    for (int face = 0; face < NB_FACES; face++) {
        const char c = s->in_forder[face];
        int direction;

        if (c == '\0') {
            av_log(ctx, AV_LOG_ERROR,
                   "Incomplete in_forder option. Direction for all 6 faces should be specified.\n");
            return AVERROR(EINVAL);
        }

        direction = get_direction(c);
        if (direction == -1) {
            av_log(ctx, AV_LOG_ERROR,
                   "Incorrect direction symbol '%c' in in_forder option.\n", c);
            return AVERROR(EINVAL);
        }

        s->in_cubemap_face_order[direction] = face;
    }

    for (int face = 0; face < NB_FACES; face++) {
        const char c = s->in_frot[face];
        int rotation;

        if (c == '\0') {
            av_log(ctx, AV_LOG_ERROR,
                   "Incomplete in_frot option. Rotation for all 6 faces should be specified.\n");
            return AVERROR(EINVAL);
        }

        rotation = get_rotation(c);
        if (rotation == -1) {
            av_log(ctx, AV_LOG_ERROR,
                   "Incorrect rotation symbol '%c' in in_frot option.\n", c);
            return AVERROR(EINVAL);
        }

        s->in_cubemap_face_rotation[face] = rotation;
    }

    return 0;
}