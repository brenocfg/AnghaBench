#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ mf_refc; scalar_t__ mf_cid; } ;
typedef  TYPE_1__ mntfs ;

/* Variables and functions */
 int /*<<< orphan*/  untimeout (scalar_t__) ; 

mntfs *
dup_mntfs(mntfs *mf)
{
  if (mf->mf_refc == 0) {
    if (mf->mf_cid)
      untimeout(mf->mf_cid);
    mf->mf_cid = 0;
  }
  mf->mf_refc++;

  return mf;
}