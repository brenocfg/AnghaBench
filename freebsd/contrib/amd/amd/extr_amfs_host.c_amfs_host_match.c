#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* opt_rfs; } ;
typedef  TYPE_1__ am_opts ;
struct TYPE_6__ {char* (* fs_match ) (TYPE_1__*) ;} ;
typedef  TYPE_2__ am_ops ;

/* Variables and functions */
 char* stub1 (TYPE_1__*) ; 

__attribute__((used)) static char *
amfs_host_match(am_opts *fo)
{
  extern am_ops nfs_ops;

  /*
   * Make sure rfs is specified to keep nfs_match happy...
   */
  if (!fo->opt_rfs)
    fo->opt_rfs = "/";

  return (*nfs_ops.fs_match) (fo);
}