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
struct TYPE_5__ {TYPE_1__* bundle; scalar_t__ col_lastval; int /*<<< orphan*/ * col_high; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; int /*<<< orphan*/  cur_ptr; int /*<<< orphan*/  cur_dec; int /*<<< orphan*/  tree; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ BinkContext ;

/* Variables and functions */
 int BINK_SRC_COLORS ; 
 int BINK_SRC_INTER_DC ; 
 int BINK_SRC_INTRA_DC ; 
 int read_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_bundle(GetBitContext *gb, BinkContext *c, int bundle_num)
{
    int i;

    if (bundle_num == BINK_SRC_COLORS) {
        for (i = 0; i < 16; i++) {
            int ret = read_tree(gb, &c->col_high[i]);
            if (ret < 0)
                return ret;
        }
        c->col_lastval = 0;
    }
    if (bundle_num != BINK_SRC_INTRA_DC && bundle_num != BINK_SRC_INTER_DC) {
        int ret = read_tree(gb, &c->bundle[bundle_num].tree);
        if (ret < 0)
            return ret;
    }
    c->bundle[bundle_num].cur_dec =
    c->bundle[bundle_num].cur_ptr = c->bundle[bundle_num].data;

    return 0;
}