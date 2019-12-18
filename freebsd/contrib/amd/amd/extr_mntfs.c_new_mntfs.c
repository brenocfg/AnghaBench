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
typedef  int /*<<< orphan*/  mntfs ;
typedef  int /*<<< orphan*/  am_opts ;

/* Variables and functions */
 int /*<<< orphan*/ * alloc_mntfs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  amfs_error_ops ; 

mntfs *
new_mntfs(void)
{
  return alloc_mntfs(&amfs_error_ops, (am_opts *) NULL, "//nil//", ".", "", "", "");
}