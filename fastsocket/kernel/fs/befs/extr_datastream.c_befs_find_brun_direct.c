#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct TYPE_6__ {scalar_t__ max_direct_range; TYPE_2__* direct; } ;
typedef  TYPE_1__ befs_data_stream ;
typedef  scalar_t__ befs_blocknr_t ;
struct TYPE_7__ {scalar_t__ len; scalar_t__ start; int /*<<< orphan*/  allocation_group; } ;
typedef  TYPE_2__ befs_block_run ;
struct TYPE_8__ {scalar_t__ block_shift; } ;

/* Variables and functions */
 int BEFS_ERR ; 
 int BEFS_NUM_DIRECT_BLOCKS ; 
 int BEFS_OK ; 
 TYPE_5__* BEFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  befs_debug (struct super_block*,char*,...) ; 
 int /*<<< orphan*/  befs_error (struct super_block*,char*) ; 

__attribute__((used)) static int
befs_find_brun_direct(struct super_block *sb, befs_data_stream * data,
		      befs_blocknr_t blockno, befs_block_run * run)
{
	int i;
	befs_block_run *array = data->direct;
	befs_blocknr_t sum;
	befs_blocknr_t max_block =
	    data->max_direct_range >> BEFS_SB(sb)->block_shift;

	befs_debug(sb, "---> befs_find_brun_direct(), find %lu", blockno);

	if (blockno > max_block) {
		befs_error(sb, "befs_find_brun_direct() passed block outside of"
			   "direct region");
		return BEFS_ERR;
	}

	for (i = 0, sum = 0; i < BEFS_NUM_DIRECT_BLOCKS;
	     sum += array[i].len, i++) {
		if (blockno >= sum && blockno < sum + (array[i].len)) {
			int offset = blockno - sum;
			run->allocation_group = array[i].allocation_group;
			run->start = array[i].start + offset;
			run->len = array[i].len - offset;

			befs_debug(sb, "---> befs_find_brun_direct(), "
				   "found %lu at direct[%d]", blockno, i);
			return BEFS_OK;
		}
	}

	befs_debug(sb, "---> befs_find_brun_direct() ERROR");
	return BEFS_ERR;
}