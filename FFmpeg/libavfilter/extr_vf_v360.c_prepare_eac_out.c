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
struct TYPE_4__ {void** out_cubemap_face_rotation; int /*<<< orphan*/ * out_cubemap_direction_order; } ;
typedef  TYPE_1__ V360Context ;
struct TYPE_5__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  BACK ; 
 size_t BOTTOM_LEFT ; 
 size_t BOTTOM_MIDDLE ; 
 size_t BOTTOM_RIGHT ; 
 int /*<<< orphan*/  DOWN ; 
 int /*<<< orphan*/  FRONT ; 
 int /*<<< orphan*/  LEFT ; 
 int /*<<< orphan*/  RIGHT ; 
 void* ROT_0 ; 
 void* ROT_270 ; 
 void* ROT_90 ; 
 size_t TOP_LEFT ; 
 size_t TOP_MIDDLE ; 
 size_t TOP_RIGHT ; 
 int /*<<< orphan*/  UP ; 

__attribute__((used)) static int prepare_eac_out(AVFilterContext *ctx)
{
    V360Context *s = ctx->priv;

    s->out_cubemap_direction_order[TOP_LEFT]      = LEFT;
    s->out_cubemap_direction_order[TOP_MIDDLE]    = FRONT;
    s->out_cubemap_direction_order[TOP_RIGHT]     = RIGHT;
    s->out_cubemap_direction_order[BOTTOM_LEFT]   = DOWN;
    s->out_cubemap_direction_order[BOTTOM_MIDDLE] = BACK;
    s->out_cubemap_direction_order[BOTTOM_RIGHT]  = UP;

    s->out_cubemap_face_rotation[TOP_LEFT]      = ROT_0;
    s->out_cubemap_face_rotation[TOP_MIDDLE]    = ROT_0;
    s->out_cubemap_face_rotation[TOP_RIGHT]     = ROT_0;
    s->out_cubemap_face_rotation[BOTTOM_LEFT]   = ROT_270;
    s->out_cubemap_face_rotation[BOTTOM_MIDDLE] = ROT_90;
    s->out_cubemap_face_rotation[BOTTOM_RIGHT]  = ROT_270;

    return 0;
}