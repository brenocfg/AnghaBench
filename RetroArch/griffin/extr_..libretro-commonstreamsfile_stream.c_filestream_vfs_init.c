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
struct retro_vfs_interface {int /*<<< orphan*/ * rename; int /*<<< orphan*/ * remove; int /*<<< orphan*/ * flush; int /*<<< orphan*/ * write; int /*<<< orphan*/ * read; int /*<<< orphan*/ * seek; int /*<<< orphan*/ * tell; int /*<<< orphan*/ * truncate; int /*<<< orphan*/ * size; int /*<<< orphan*/ * close; int /*<<< orphan*/ * open; int /*<<< orphan*/ * get_path; } ;

/* Variables and functions */
 scalar_t__ FILESTREAM_REQUIRED_VFS_VERSION ; 
 int /*<<< orphan*/ * filestream_close_cb ; 
 int /*<<< orphan*/ * filestream_flush_cb ; 
 int /*<<< orphan*/ * filestream_get_path_cb ; 
 int /*<<< orphan*/ * filestream_open_cb ; 
 int /*<<< orphan*/ * filestream_read_cb ; 
 int /*<<< orphan*/ * filestream_remove_cb ; 
 int /*<<< orphan*/ * filestream_rename_cb ; 
 int /*<<< orphan*/ * filestream_seek_cb ; 
 int /*<<< orphan*/ * filestream_size_cb ; 
 int /*<<< orphan*/ * filestream_tell_cb ; 
 int /*<<< orphan*/ * filestream_truncate_cb ; 
 int /*<<< orphan*/ * filestream_write_cb ; 

void filestream_vfs_init(const struct retro_vfs_interface_info* vfs_info)
{
   const struct retro_vfs_interface* vfs_iface;

   filestream_get_path_cb = NULL;
   filestream_open_cb     = NULL;
   filestream_close_cb    = NULL;
   filestream_tell_cb     = NULL;
   filestream_size_cb     = NULL;
   filestream_truncate_cb = NULL;
   filestream_seek_cb     = NULL;
   filestream_read_cb     = NULL;
   filestream_write_cb    = NULL;
   filestream_flush_cb    = NULL;
   filestream_remove_cb   = NULL;
   filestream_rename_cb   = NULL;

   vfs_iface              = vfs_info->iface;

   if (vfs_info->required_interface_version < FILESTREAM_REQUIRED_VFS_VERSION
         || !vfs_iface)
      return;

   filestream_get_path_cb = vfs_iface->get_path;
   filestream_open_cb     = vfs_iface->open;
   filestream_close_cb    = vfs_iface->close;
   filestream_size_cb     = vfs_iface->size;
   filestream_truncate_cb = vfs_iface->truncate;
   filestream_tell_cb     = vfs_iface->tell;
   filestream_seek_cb     = vfs_iface->seek;
   filestream_read_cb     = vfs_iface->read;
   filestream_write_cb    = vfs_iface->write;
   filestream_flush_cb    = vfs_iface->flush;
   filestream_remove_cb   = vfs_iface->remove;
   filestream_rename_cb   = vfs_iface->rename;
}