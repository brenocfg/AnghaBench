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
struct TYPE_5__ {int /*<<< orphan*/  hcoeff; int /*<<< orphan*/  last_hcoeff; int /*<<< orphan*/  htaps; int /*<<< orphan*/  last_htaps; int /*<<< orphan*/  diag_mc; int /*<<< orphan*/  last_diag_mc; } ;
struct TYPE_4__ {int /*<<< orphan*/  spatial_decomposition_count; int /*<<< orphan*/  last_spatial_decomposition_count; int /*<<< orphan*/  block_max_depth; int /*<<< orphan*/  last_block_max_depth; int /*<<< orphan*/  mv_scale; int /*<<< orphan*/  last_mv_scale; int /*<<< orphan*/  qbias; int /*<<< orphan*/  last_qbias; int /*<<< orphan*/  qlog; int /*<<< orphan*/  last_qlog; int /*<<< orphan*/  spatial_decomposition_type; int /*<<< orphan*/  last_spatial_decomposition_type; TYPE_2__* plane; int /*<<< orphan*/  keyframe; } ;
typedef  TYPE_1__ SnowContext ;
typedef  TYPE_2__ Plane ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void update_last_header_values(SnowContext *s){
    int plane_index;

    if(!s->keyframe){
        for(plane_index=0; plane_index<2; plane_index++){
            Plane *p= &s->plane[plane_index];
            p->last_diag_mc= p->diag_mc;
            p->last_htaps  = p->htaps;
            memcpy(p->last_hcoeff, p->hcoeff, sizeof(p->hcoeff));
        }
    }

    s->last_spatial_decomposition_type  = s->spatial_decomposition_type;
    s->last_qlog                        = s->qlog;
    s->last_qbias                       = s->qbias;
    s->last_mv_scale                    = s->mv_scale;
    s->last_block_max_depth             = s->block_max_depth;
    s->last_spatial_decomposition_count = s->spatial_decomposition_count;
}