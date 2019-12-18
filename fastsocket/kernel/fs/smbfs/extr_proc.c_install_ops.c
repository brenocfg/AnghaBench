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
struct smb_ops {int dummy; } ;

/* Variables and functions */
 int SMB_OPS_NUM_STATIC ; 
 int /*<<< orphan*/  memcpy (struct smb_ops*,struct smb_ops*,int) ; 

__attribute__((used)) static void
install_ops(struct smb_ops *dst, struct smb_ops *src)
{
	memcpy(dst, src, sizeof(void *) * SMB_OPS_NUM_STATIC);
}