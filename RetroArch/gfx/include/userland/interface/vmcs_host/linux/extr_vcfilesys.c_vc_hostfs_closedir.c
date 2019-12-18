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
struct fs_dir {int /*<<< orphan*/ * dhandle; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_MINOR (char*,void*) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct fs_dir*) ; 

int vc_hostfs_closedir(void *dhandle)
{
   struct fs_dir *fsdir = (struct fs_dir *)dhandle;
   int ret = -1;

   DEBUG_MINOR( "vc_hostfs_closedir(%p)", dhandle );

   if (dhandle && fsdir->dhandle)
   {
      (void)closedir(fsdir->dhandle);
      fsdir->dhandle = NULL;
      free(fsdir);
      ret = 0;
   }

   return ret;
}