#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct AVTreeNode {void* ts; void* back_ptr; void* pos; } ;
typedef  void* int64_t ;
struct TYPE_3__ {int /*<<< orphan*/  syncpoints; int /*<<< orphan*/  sp_count; } ;
typedef  struct AVTreeNode Syncpoint ;
typedef  TYPE_1__ NUTContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_free (struct AVTreeNode*) ; 
 int /*<<< orphan*/  av_freep (struct AVTreeNode**) ; 
 struct AVTreeNode* av_mallocz (int) ; 
 int /*<<< orphan*/  av_tree_insert (int /*<<< orphan*/ *,struct AVTreeNode*,int /*<<< orphan*/ ,struct AVTreeNode**) ; 
 struct AVTreeNode* av_tree_node_alloc () ; 
 int /*<<< orphan*/  ff_nut_sp_pos_cmp ; 

int ff_nut_add_sp(NUTContext *nut, int64_t pos, int64_t back_ptr, int64_t ts)
{
    Syncpoint *sp           = av_mallocz(sizeof(Syncpoint));
    struct AVTreeNode *node = av_tree_node_alloc();

    if (!sp || !node) {
        av_freep(&sp);
        av_freep(&node);
        return AVERROR(ENOMEM);
    }

    nut->sp_count++;

    sp->pos      = pos;
    sp->back_ptr = back_ptr;
    sp->ts       = ts;
    av_tree_insert(&nut->syncpoints, sp, ff_nut_sp_pos_cmp, &node);
    if (node) {
        av_free(sp);
        av_free(node);
    }

    return 0;
}