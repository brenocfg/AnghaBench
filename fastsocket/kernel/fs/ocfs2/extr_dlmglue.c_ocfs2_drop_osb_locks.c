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
struct TYPE_2__ {int /*<<< orphan*/  os_lockres; } ;
struct ocfs2_super {TYPE_1__ osb_orphan_scan; int /*<<< orphan*/  osb_nfs_sync_lockres; int /*<<< orphan*/  osb_rename_lockres; int /*<<< orphan*/  osb_super_lockres; } ;

/* Variables and functions */
 int /*<<< orphan*/  ocfs2_simple_drop_lockres (struct ocfs2_super*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ocfs2_drop_osb_locks(struct ocfs2_super *osb)
{
	ocfs2_simple_drop_lockres(osb, &osb->osb_super_lockres);
	ocfs2_simple_drop_lockres(osb, &osb->osb_rename_lockres);
	ocfs2_simple_drop_lockres(osb, &osb->osb_nfs_sync_lockres);
	ocfs2_simple_drop_lockres(osb, &osb->osb_orphan_scan.os_lockres);
}