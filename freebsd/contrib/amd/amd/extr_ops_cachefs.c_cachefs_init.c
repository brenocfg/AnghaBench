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
typedef  scalar_t__ voidp ;
struct TYPE_5__ {void (* mf_prfree ) (scalar_t__) ;TYPE_1__* mf_fo; scalar_t__ mf_private; } ;
typedef  TYPE_2__ mntfs ;
struct TYPE_4__ {int /*<<< orphan*/  opt_cachedir; } ;

/* Variables and functions */
 scalar_t__ free ; 
 scalar_t__ xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cachefs_init(mntfs *mf)
{
  /*
   * Save cache directory name
   */
  if (!mf->mf_private) {
    mf->mf_private = (voidp) xstrdup(mf->mf_fo->opt_cachedir);
    mf->mf_prfree = (void (*)(voidp)) free;
  }

  return 0;
}