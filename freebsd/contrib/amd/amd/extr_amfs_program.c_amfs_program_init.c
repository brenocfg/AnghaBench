#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* opaque_t ;
struct TYPE_5__ {void (* mf_prfree ) (void*) ;TYPE_1__* mf_fo; int /*<<< orphan*/ * mf_private; } ;
typedef  TYPE_2__ mntfs ;
struct TYPE_4__ {int /*<<< orphan*/ * opt_umount; int /*<<< orphan*/ * opt_unmount; } ;

/* Variables and functions */
 scalar_t__ free ; 
 scalar_t__ xstrdup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
amfs_program_init(mntfs *mf)
{
  /* check if already saved value */
  if (mf->mf_private != NULL)
    return 0;

  if (mf->mf_fo == NULL)
    return 0;

  /* save unmount (or umount) command */
  if (mf->mf_fo->opt_unmount != NULL)
    mf->mf_private = (opaque_t) xstrdup(mf->mf_fo->opt_unmount);
  else
    mf->mf_private = (opaque_t) xstrdup(mf->mf_fo->opt_umount);
  mf->mf_prfree = (void (*)(opaque_t)) free;

  return 0;
}