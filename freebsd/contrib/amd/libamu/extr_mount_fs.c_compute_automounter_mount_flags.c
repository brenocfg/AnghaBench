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
typedef  int /*<<< orphan*/  mntent_t ;

/* Variables and functions */
 int MNT2_GEN_OPT_AUTOMNTFS ; 
 int MNT2_GEN_OPT_IGNORE ; 

int
compute_automounter_mount_flags(mntent_t *mntp)
{
  int flags = 0;

#ifdef MNT2_GEN_OPT_IGNORE
  flags |= MNT2_GEN_OPT_IGNORE;
#endif /* not MNT2_GEN_OPT_IGNORE */
#ifdef MNT2_GEN_OPT_AUTOMNTFS
  flags |= MNT2_GEN_OPT_AUTOMNTFS;
#endif /* not MNT2_GEN_OPT_AUTOMNTFS */

  return flags;
}