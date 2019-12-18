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
struct smb_sb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SB_of (struct smb_sb_info*) ; 
 int /*<<< orphan*/  VERBOSE (char*) ; 
 int /*<<< orphan*/  invalidate_inodes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shrink_dcache_sb (int /*<<< orphan*/ ) ; 

void
smb_invalidate_inodes(struct smb_sb_info *server)
{
	VERBOSE("\n");
	shrink_dcache_sb(SB_of(server));
	invalidate_inodes(SB_of(server));
}