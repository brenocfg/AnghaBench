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
struct TYPE_9__ {int /*<<< orphan*/ * stat_desc; int /*<<< orphan*/  dyn_tree; } ;
struct TYPE_8__ {int /*<<< orphan*/ * stat_desc; int /*<<< orphan*/  dyn_tree; } ;
struct TYPE_7__ {int /*<<< orphan*/ * stat_desc; int /*<<< orphan*/  dyn_tree; } ;
struct TYPE_10__ {long compressed_len; int last_eob_len; long bits_sent; scalar_t__ bi_valid; scalar_t__ bi_buf; TYPE_3__ bl_desc; int /*<<< orphan*/  bl_tree; TYPE_2__ d_desc; int /*<<< orphan*/  dyn_dtree; TYPE_1__ l_desc; int /*<<< orphan*/  dyn_ltree; } ;
typedef  TYPE_4__ deflate_state ;

/* Variables and functions */
 int /*<<< orphan*/  init_block (TYPE_4__*) ; 
 int /*<<< orphan*/  static_bl_desc ; 
 int /*<<< orphan*/  static_d_desc ; 
 int /*<<< orphan*/  static_l_desc ; 
 int /*<<< orphan*/  tr_static_init () ; 

void zlib_tr_init(
	deflate_state *s
)
{
    tr_static_init();

    s->compressed_len = 0L;

    s->l_desc.dyn_tree = s->dyn_ltree;
    s->l_desc.stat_desc = &static_l_desc;

    s->d_desc.dyn_tree = s->dyn_dtree;
    s->d_desc.stat_desc = &static_d_desc;

    s->bl_desc.dyn_tree = s->bl_tree;
    s->bl_desc.stat_desc = &static_bl_desc;

    s->bi_buf = 0;
    s->bi_valid = 0;
    s->last_eob_len = 8; /* enough lookahead for inflate */
#ifdef DEBUG_ZLIB
    s->bits_sent = 0L;
#endif

    /* Initialize the first block of the first file: */
    init_block(s);
}