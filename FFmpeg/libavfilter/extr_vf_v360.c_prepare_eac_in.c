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
struct TYPE_4__ {size_t* in_cubemap_face_order; void** in_cubemap_face_rotation; scalar_t__ iv_flip; scalar_t__ ih_flip; } ;
typedef  TYPE_1__ V360Context ;
struct TYPE_5__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 size_t BACK ; 
 size_t BOTTOM_LEFT ; 
 size_t BOTTOM_MIDDLE ; 
 size_t BOTTOM_RIGHT ; 
 size_t DOWN ; 
 size_t FRONT ; 
 size_t LEFT ; 
 size_t RIGHT ; 
 void* ROT_0 ; 
 void* ROT_270 ; 
 void* ROT_90 ; 
 size_t TOP_LEFT ; 
 size_t TOP_MIDDLE ; 
 size_t TOP_RIGHT ; 
 size_t UP ; 

__attribute__((used)) static int prepare_eac_in(AVFilterContext *ctx)
{
    V360Context *s = ctx->priv;

    if (s->ih_flip && s->iv_flip) {
        s->in_cubemap_face_order[RIGHT] = BOTTOM_LEFT;
        s->in_cubemap_face_order[LEFT]  = BOTTOM_RIGHT;
        s->in_cubemap_face_order[UP]    = TOP_LEFT;
        s->in_cubemap_face_order[DOWN]  = TOP_RIGHT;
        s->in_cubemap_face_order[FRONT] = BOTTOM_MIDDLE;
        s->in_cubemap_face_order[BACK]  = TOP_MIDDLE;
    } else if (s->ih_flip) {
        s->in_cubemap_face_order[RIGHT] = TOP_LEFT;
        s->in_cubemap_face_order[LEFT]  = TOP_RIGHT;
        s->in_cubemap_face_order[UP]    = BOTTOM_LEFT;
        s->in_cubemap_face_order[DOWN]  = BOTTOM_RIGHT;
        s->in_cubemap_face_order[FRONT] = TOP_MIDDLE;
        s->in_cubemap_face_order[BACK]  = BOTTOM_MIDDLE;
    } else if (s->iv_flip) {
        s->in_cubemap_face_order[RIGHT] = BOTTOM_RIGHT;
        s->in_cubemap_face_order[LEFT]  = BOTTOM_LEFT;
        s->in_cubemap_face_order[UP]    = TOP_RIGHT;
        s->in_cubemap_face_order[DOWN]  = TOP_LEFT;
        s->in_cubemap_face_order[FRONT] = BOTTOM_MIDDLE;
        s->in_cubemap_face_order[BACK]  = TOP_MIDDLE;
    } else {
        s->in_cubemap_face_order[RIGHT] = TOP_RIGHT;
        s->in_cubemap_face_order[LEFT]  = TOP_LEFT;
        s->in_cubemap_face_order[UP]    = BOTTOM_RIGHT;
        s->in_cubemap_face_order[DOWN]  = BOTTOM_LEFT;
        s->in_cubemap_face_order[FRONT] = TOP_MIDDLE;
        s->in_cubemap_face_order[BACK]  = BOTTOM_MIDDLE;
    }

    if (s->iv_flip) {
        s->in_cubemap_face_rotation[TOP_LEFT]      = ROT_270;
        s->in_cubemap_face_rotation[TOP_MIDDLE]    = ROT_90;
        s->in_cubemap_face_rotation[TOP_RIGHT]     = ROT_270;
        s->in_cubemap_face_rotation[BOTTOM_LEFT]   = ROT_0;
        s->in_cubemap_face_rotation[BOTTOM_MIDDLE] = ROT_0;
        s->in_cubemap_face_rotation[BOTTOM_RIGHT]  = ROT_0;
    } else {
        s->in_cubemap_face_rotation[TOP_LEFT]      = ROT_0;
        s->in_cubemap_face_rotation[TOP_MIDDLE]    = ROT_0;
        s->in_cubemap_face_rotation[TOP_RIGHT]     = ROT_0;
        s->in_cubemap_face_rotation[BOTTOM_LEFT]   = ROT_270;
        s->in_cubemap_face_rotation[BOTTOM_MIDDLE] = ROT_90;
        s->in_cubemap_face_rotation[BOTTOM_RIGHT]  = ROT_270;
    }

    return 0;
}