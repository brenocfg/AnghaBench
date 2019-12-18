#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int mf_flags; } ;
typedef  TYPE_1__ mntfs ;
struct TYPE_9__ {int /*<<< orphan*/  (* umounted ) (TYPE_1__*) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  (* umounted ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int MFF_NFSLINK ; 
 TYPE_6__ amfs_link_ops ; 
 TYPE_4__ nfs_ops ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*) ; 

__attribute__((used)) static void
amfs_nfsl_umounted(mntfs *mf)
{
  if (mf->mf_flags & MFF_NFSLINK) {
    if (amfs_link_ops.umounted)
      amfs_link_ops.umounted(mf);
  } else {
    if (nfs_ops.umounted)
      nfs_ops.umounted(mf);
  }
}