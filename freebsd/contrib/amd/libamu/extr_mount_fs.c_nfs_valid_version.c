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
typedef  scalar_t__ u_long ;

/* Variables and functions */
 scalar_t__ NFS_VERS_MAX ; 
 scalar_t__ NFS_VERS_MIN ; 

int
nfs_valid_version(u_long v)
{
  return v >= NFS_VERS_MIN && v <= NFS_VERS_MAX;
}