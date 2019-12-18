#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_4__* th; scalar_t__ prealloc_size; TYPE_2__* inode; scalar_t__ preallocate; int /*<<< orphan*/  formatted_node; } ;
typedef  TYPE_5__ reiserfs_blocknr_hint_t ;
struct TYPE_10__ {int preallocmin; scalar_t__ preallocsize; } ;
struct TYPE_13__ {TYPE_3__ s_alloc_options; } ;
struct TYPE_11__ {int /*<<< orphan*/  t_super; } ;
struct TYPE_9__ {int i_size; TYPE_1__* i_sb; int /*<<< orphan*/  i_mode; } ;
struct TYPE_8__ {int s_blocksize; } ;

/* Variables and functions */
 int CARRY_ON ; 
 TYPE_7__* REISERFS_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int determine_prealloc_size(reiserfs_blocknr_hint_t * hint)
{
	/* make minimum size a mount option and benchmark both ways */
	/* we preallocate blocks only for regular files, specific size */
	/* benchmark preallocating always and see what happens */

	hint->prealloc_size = 0;

	if (!hint->formatted_node && hint->preallocate) {
		if (S_ISREG(hint->inode->i_mode)
		    && hint->inode->i_size >=
		    REISERFS_SB(hint->th->t_super)->s_alloc_options.
		    preallocmin * hint->inode->i_sb->s_blocksize)
			hint->prealloc_size =
			    REISERFS_SB(hint->th->t_super)->s_alloc_options.
			    preallocsize - 1;
	}
	return CARRY_ON;
}