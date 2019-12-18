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
struct opt_tab {int flag; scalar_t__ opt; } ;
typedef  int /*<<< orphan*/  mntent_t ;

/* Variables and functions */
 int MNT2_GEN_OPT_AUTOMOUNTED ; 
 int MNT2_GEN_OPT_NEWTYPE ; 
 scalar_t__ amu_hasmntopt (int /*<<< orphan*/ *,scalar_t__) ; 
 struct opt_tab* mnt_flags ; 

int
compute_mount_flags(mntent_t *mntp)
{
  struct opt_tab *opt;
  int flags = 0;

#ifdef MNT2_GEN_OPT_NEWTYPE
  flags |= MNT2_GEN_OPT_NEWTYPE;
#endif /* MNT2_GEN_OPT_NEWTYPE */
#ifdef MNT2_GEN_OPT_AUTOMOUNTED
  flags |= MNT2_GEN_OPT_AUTOMOUNTED;
#endif /* not MNT2_GEN_OPT_AUTOMOUNTED */

  /*
   * Crack basic mount options
   */
  for (opt = mnt_flags; opt->opt; opt++) {
    flags |= amu_hasmntopt(mntp, opt->opt) ? opt->flag : 0;
  }

  return flags;
}