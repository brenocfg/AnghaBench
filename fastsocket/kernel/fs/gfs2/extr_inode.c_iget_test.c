#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct inode {int i_state; } ;
struct gfs2_skip_data {scalar_t__ no_addr; int skipped; scalar_t__ non_block; } ;
struct gfs2_inode {scalar_t__ i_no_addr; } ;

/* Variables and functions */
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 int I_CLEAR ; 
 int I_FREEING ; 
 int I_WILL_FREE ; 

__attribute__((used)) static int iget_test(struct inode *inode, void *opaque)
{
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_skip_data *data = opaque;

	if (ip->i_no_addr == data->no_addr) {
		if (data->non_block &&
		    inode->i_state & (I_FREEING|I_CLEAR|I_WILL_FREE)) {
			data->skipped = 1;
			return 0;
		}
		return 1;
	}
	return 0;
}