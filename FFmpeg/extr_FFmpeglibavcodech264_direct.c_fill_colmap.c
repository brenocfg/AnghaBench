#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  map ;
struct TYPE_10__ {scalar_t__ picture_structure; } ;
struct TYPE_9__ {int** ref_count; int*** ref_poc; int frame_num; scalar_t__ mbaff; } ;
struct TYPE_8__ {int* ref_count; TYPE_1__** ref_list; } ;
struct TYPE_7__ {int reference; TYPE_3__* parent; } ;
typedef  TYPE_2__ H264SliceContext ;
typedef  TYPE_3__ H264Picture ;
typedef  TYPE_4__ H264Context ;

/* Variables and functions */
 scalar_t__ PICT_FRAME ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fill_colmap(const H264Context *h, H264SliceContext *sl,
                        int map[2][16 + 32], int list,
                        int field, int colfield, int mbafi)
{
    H264Picture *const ref1 = sl->ref_list[1][0].parent;
    int j, old_ref, rfield;
    int start  = mbafi ? 16                       : 0;
    int end    = mbafi ? 16 + 2 * sl->ref_count[0] : sl->ref_count[0];
    int interl = mbafi || h->picture_structure != PICT_FRAME;

    /* bogus; fills in for missing frames */
    memset(map[list], 0, sizeof(map[list]));

    for (rfield = 0; rfield < 2; rfield++) {
        for (old_ref = 0; old_ref < ref1->ref_count[colfield][list]; old_ref++) {
            int poc = ref1->ref_poc[colfield][list][old_ref];

            if (!interl)
                poc |= 3;
            // FIXME: store all MBAFF references so this is not needed
            else if (interl && (poc & 3) == 3)
                poc = (poc & ~3) + rfield + 1;

            for (j = start; j < end; j++) {
                if (4 * sl->ref_list[0][j].parent->frame_num +
                    (sl->ref_list[0][j].reference & 3) == poc) {
                    int cur_ref = mbafi ? (j - 16) ^ field : j;
                    if (ref1->mbaff)
                        map[list][2 * old_ref + (rfield ^ field) + 16] = cur_ref;
                    if (rfield == field || !interl)
                        map[list][old_ref] = cur_ref;
                    break;
                }
            }
        }
    }
}