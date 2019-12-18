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
typedef  scalar_t__ opaque_t ;
struct TYPE_5__ {int /*<<< orphan*/  mf_prfree; int /*<<< orphan*/  mf_mount; TYPE_1__* mf_fo; int /*<<< orphan*/  mf_info; scalar_t__ mf_private; } ;
typedef  TYPE_2__ mntfs ;
struct TYPE_4__ {char* opt_cache; int /*<<< orphan*/ * opt_maptype; } ;

/* Variables and functions */
 scalar_t__ mapc_find (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapc_free ; 

void
amfs_mkcacheref(mntfs *mf)
{
  char *cache;

  if (mf->mf_fo && mf->mf_fo->opt_cache)
    cache = mf->mf_fo->opt_cache;
  else
    cache = "none";
  mf->mf_private = (opaque_t) mapc_find(mf->mf_info,
					cache,
					(mf->mf_fo ? mf->mf_fo->opt_maptype : NULL),
					mf->mf_mount);
  mf->mf_prfree = mapc_free;
}