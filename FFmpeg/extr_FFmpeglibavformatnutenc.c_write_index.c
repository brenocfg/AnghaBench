#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_11__ {int nb_streams; } ;
struct TYPE_10__ {scalar_t__ sp_count; TYPE_7__* avf; TYPE_2__* stream; int /*<<< orphan*/  syncpoints; int /*<<< orphan*/  max_pts; int /*<<< orphan*/  max_pts_tb; } ;
struct TYPE_9__ {scalar_t__* keyframe_pts; } ;
struct TYPE_8__ {int pos; } ;
typedef  TYPE_1__ Syncpoint ;
typedef  TYPE_2__ StreamContext ;
typedef  TYPE_3__ NUTContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*) ; 
 int av_log2 (scalar_t__) ; 
 int /*<<< orphan*/  av_tree_find (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,void**) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wb64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ff_nut_sp_pos_cmp ; 
 int /*<<< orphan*/  ff_put_v (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  put_tt (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int write_index(NUTContext *nut, AVIOContext *bc) {
    int i;
    Syncpoint dummy= { .pos= 0 };
    Syncpoint *next_node[2] = { NULL };
    int64_t startpos = avio_tell(bc);
    int64_t payload_size;

    put_tt(nut, nut->max_pts_tb, bc, nut->max_pts);

    ff_put_v(bc, nut->sp_count);

    for (i=0; i<nut->sp_count; i++) {
        av_tree_find(nut->syncpoints, &dummy, ff_nut_sp_pos_cmp, (void**)next_node);
        ff_put_v(bc, (next_node[1]->pos >> 4) - (dummy.pos>>4));
        dummy.pos = next_node[1]->pos;
    }

    for (i=0; i<nut->avf->nb_streams; i++) {
        StreamContext *nus= &nut->stream[i];
        int64_t last_pts= -1;
        int j, k;
        for (j=0; j<nut->sp_count; j++) {
            int flag;
            int n = 0;

            if (j && nus->keyframe_pts[j] == nus->keyframe_pts[j-1]) {
                av_log(nut->avf, AV_LOG_WARNING, "Multiple keyframes with same PTS\n");
                nus->keyframe_pts[j] = AV_NOPTS_VALUE;
            }

            flag = (nus->keyframe_pts[j] != AV_NOPTS_VALUE) ^ (j+1 == nut->sp_count);
            for (; j<nut->sp_count && (nus->keyframe_pts[j] != AV_NOPTS_VALUE) == flag; j++)
                n++;

            ff_put_v(bc, 1 + 2*flag + 4*n);
            for (k= j - n; k<=j && k<nut->sp_count; k++) {
                if (nus->keyframe_pts[k] == AV_NOPTS_VALUE)
                    continue;
                av_assert0(nus->keyframe_pts[k] > last_pts);
                ff_put_v(bc, nus->keyframe_pts[k] - last_pts);
                last_pts = nus->keyframe_pts[k];
            }
        }
    }

    payload_size = avio_tell(bc) - startpos + 8 + 4;

    avio_wb64(bc, 8 + payload_size + av_log2(payload_size) / 7 + 1 + 4*(payload_size > 4096));

    return 0;
}