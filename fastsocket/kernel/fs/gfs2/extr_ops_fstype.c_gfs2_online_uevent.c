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
struct super_block {int s_flags; } ;
struct TYPE_2__ {scalar_t__ ar_spectator; } ;
struct gfs2_sbd {int /*<<< orphan*/  sd_kobj; TYPE_1__ sd_args; struct super_block* sd_vfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_ONLINE ; 
 int MS_RDONLY ; 
 int /*<<< orphan*/  kobject_uevent_env (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

void gfs2_online_uevent(struct gfs2_sbd *sdp)
{
	struct super_block *sb = sdp->sd_vfs;
	char ro[20];
	char spectator[20];
	char *envp[] = { ro, spectator, NULL };
	sprintf(ro, "RDONLY=%d", (sb->s_flags & MS_RDONLY) ? 1 : 0);
	sprintf(spectator, "SPECTATOR=%d", sdp->sd_args.ar_spectator ? 1 : 0);
	kobject_uevent_env(&sdp->sd_kobj, KOBJ_ONLINE, envp);
}