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
struct TYPE_2__ {int /*<<< orphan*/  max_xmit; } ;
struct smb_sb_info {TYPE_1__ opt; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int SMB_HEADER_LEN ; 
 int /*<<< orphan*/  VERBOSE (char*,int /*<<< orphan*/ ,int) ; 
 int smb_get_xmitsize (struct smb_sb_info*,int) ; 

int
smb_get_rsize(struct smb_sb_info *server)
{
	/* readX has 12 parameters, read has 5 */
	int overhead = SMB_HEADER_LEN + 12 * sizeof(__u16) + 2 + 1 + 2;
	int size = smb_get_xmitsize(server, overhead);

	VERBOSE("xmit=%d, size=%d\n", server->opt.max_xmit, size);

	return size;
}