#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  enum MVJoint { ____Placeholder_MVJoint } MVJoint ;
struct TYPE_20__ {int /*<<< orphan*/ * mv_joint; } ;
struct TYPE_21__ {TYPE_5__ counts; int /*<<< orphan*/  c; TYPE_8__* b; TYPE_7__* s; } ;
typedef  TYPE_6__ VP9TileData ;
struct TYPE_18__ {int /*<<< orphan*/  mv_joint; } ;
struct TYPE_19__ {TYPE_3__ p; } ;
struct TYPE_16__ {scalar_t__ highprecisionmvs; } ;
struct TYPE_17__ {TYPE_1__ h; } ;
struct TYPE_22__ {TYPE_4__ prob; TYPE_2__ s; } ;
typedef  TYPE_7__ VP9Context ;
struct TYPE_23__ {int /*<<< orphan*/ * ref; scalar_t__ comp; } ;
typedef  TYPE_8__ VP9Block ;
struct TYPE_24__ {int x; int y; } ;
typedef  TYPE_9__ VP56mv ;

/* Variables and functions */
 int /*<<< orphan*/  AV_ZERO64 (TYPE_9__*) ; 
 int MV_JOINT_V ; 
 int NEARMV ; 
 int NEWMV ; 
 int ZEROMV ; 
 int abs (int) ; 
 int /*<<< orphan*/  ff_vp9_mv_joint_tree ; 
 int /*<<< orphan*/  find_ref_mvs (TYPE_6__*,TYPE_9__*,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ read_mv_component (TYPE_6__*,int,int) ; 
 int vp8_rac_get_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ff_vp9_fill_mv(VP9TileData *td, VP56mv *mv, int mode, int sb)
{
    VP9Context *s = td->s;
    VP9Block *b = td->b;

    if (mode == ZEROMV) {
        AV_ZERO64(mv);
    } else {
        int hp;

        // FIXME cache this value and reuse for other subblocks
        find_ref_mvs(td, &mv[0], b->ref[0], 0, mode == NEARMV,
                     mode == NEWMV ? -1 : sb);
        // FIXME maybe move this code into find_ref_mvs()
        if ((mode == NEWMV || sb == -1) &&
            !(hp = s->s.h.highprecisionmvs &&
              abs(mv[0].x) < 64 && abs(mv[0].y) < 64)) {
            if (mv[0].y & 1) {
                if (mv[0].y < 0)
                    mv[0].y++;
                else
                    mv[0].y--;
            }
            if (mv[0].x & 1) {
                if (mv[0].x < 0)
                    mv[0].x++;
                else
                    mv[0].x--;
            }
        }
        if (mode == NEWMV) {
            enum MVJoint j = vp8_rac_get_tree(td->c, ff_vp9_mv_joint_tree,
                                              s->prob.p.mv_joint);

            td->counts.mv_joint[j]++;
            if (j >= MV_JOINT_V)
                mv[0].y += read_mv_component(td, 0, hp);
            if (j & 1)
                mv[0].x += read_mv_component(td, 1, hp);
        }

        if (b->comp) {
            // FIXME cache this value and reuse for other subblocks
            find_ref_mvs(td, &mv[1], b->ref[1], 1, mode == NEARMV,
                         mode == NEWMV ? -1 : sb);
            if ((mode == NEWMV || sb == -1) &&
                !(hp = s->s.h.highprecisionmvs &&
                  abs(mv[1].x) < 64 && abs(mv[1].y) < 64)) {
                if (mv[1].y & 1) {
                    if (mv[1].y < 0)
                        mv[1].y++;
                    else
                        mv[1].y--;
                }
                if (mv[1].x & 1) {
                    if (mv[1].x < 0)
                        mv[1].x++;
                    else
                        mv[1].x--;
                }
            }
            if (mode == NEWMV) {
                enum MVJoint j = vp8_rac_get_tree(td->c, ff_vp9_mv_joint_tree,
                                                  s->prob.p.mv_joint);

                td->counts.mv_joint[j]++;
                if (j >= MV_JOINT_V)
                    mv[1].y += read_mv_component(td, 0, hp);
                if (j & 1)
                    mv[1].x += read_mv_component(td, 1, hp);
            }
        }
    }
}