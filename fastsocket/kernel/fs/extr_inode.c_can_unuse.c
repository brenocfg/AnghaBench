#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ nrpages; } ;
struct inode {TYPE_1__ i_data; int /*<<< orphan*/  i_count; scalar_t__ i_state; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ inode_has_buffers (struct inode*) ; 

__attribute__((used)) static int can_unuse(struct inode *inode)
{
	if (inode->i_state)
		return 0;
	if (inode_has_buffers(inode))
		return 0;
	if (atomic_read(&inode->i_count))
		return 0;
	if (inode->i_data.nrpages)
		return 0;
	return 1;
}