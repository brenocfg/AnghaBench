#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* wchan_t ;
struct TYPE_9__ {TYPE_1__* mf_ops; } ;
typedef  TYPE_2__ mntfs ;
struct TYPE_8__ {TYPE_2__* (* get_wchan ) (TYPE_2__*) ;} ;

/* Variables and functions */
 TYPE_2__* stub1 (TYPE_2__*) ; 

wchan_t
get_mntfs_wchan(mntfs *mf)
{
  if (mf &&
      mf->mf_ops &&
      mf->mf_ops->get_wchan)
    return mf->mf_ops->get_wchan(mf);
  return mf;
}