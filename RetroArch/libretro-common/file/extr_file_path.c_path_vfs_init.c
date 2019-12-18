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
struct retro_vfs_interface_info {scalar_t__ required_interface_version; struct retro_vfs_interface* iface; } ;
struct retro_vfs_interface {int /*<<< orphan*/  mkdir; int /*<<< orphan*/  stat; } ;

/* Variables and functions */
 scalar_t__ PATH_REQUIRED_VFS_VERSION ; 
 int /*<<< orphan*/  path_mkdir_cb ; 
 int /*<<< orphan*/  path_stat_cb ; 
 int /*<<< orphan*/  retro_vfs_mkdir_impl ; 
 int /*<<< orphan*/  retro_vfs_stat_impl ; 

void path_vfs_init(const struct retro_vfs_interface_info* vfs_info)
{
   const struct retro_vfs_interface* 
      vfs_iface           = vfs_info->iface;

   path_stat_cb           = retro_vfs_stat_impl;
   path_mkdir_cb          = retro_vfs_mkdir_impl;

   if (vfs_info->required_interface_version < PATH_REQUIRED_VFS_VERSION || !vfs_iface)
      return;

   path_stat_cb           = vfs_iface->stat;
   path_mkdir_cb          = vfs_iface->mkdir;
}