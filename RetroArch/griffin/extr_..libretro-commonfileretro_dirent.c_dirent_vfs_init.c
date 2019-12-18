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
struct retro_vfs_interface {int /*<<< orphan*/ * closedir; int /*<<< orphan*/ * dirent_is_dir; int /*<<< orphan*/ * dirent_get_name; int /*<<< orphan*/ * readdir; int /*<<< orphan*/ * opendir; } ;

/* Variables and functions */
 scalar_t__ DIRENT_REQUIRED_VFS_VERSION ; 
 int /*<<< orphan*/ * dirent_closedir_cb ; 
 int /*<<< orphan*/ * dirent_dirent_get_name_cb ; 
 int /*<<< orphan*/ * dirent_dirent_is_dir_cb ; 
 int /*<<< orphan*/ * dirent_opendir_cb ; 
 int /*<<< orphan*/ * dirent_readdir_cb ; 

void dirent_vfs_init(const struct retro_vfs_interface_info* vfs_info)
{
   const struct retro_vfs_interface* vfs_iface;

   dirent_opendir_cb = NULL;
   dirent_readdir_cb = NULL;
   dirent_dirent_get_name_cb = NULL;
   dirent_dirent_is_dir_cb = NULL;
   dirent_closedir_cb = NULL;

   vfs_iface = vfs_info->iface;

   if (vfs_info->required_interface_version < DIRENT_REQUIRED_VFS_VERSION || !vfs_iface)
      return;

   dirent_opendir_cb = vfs_iface->opendir;
   dirent_readdir_cb = vfs_iface->readdir;
   dirent_dirent_get_name_cb = vfs_iface->dirent_get_name;
   dirent_dirent_is_dir_cb = vfs_iface->dirent_is_dir;
   dirent_closedir_cb = vfs_iface->closedir;
}