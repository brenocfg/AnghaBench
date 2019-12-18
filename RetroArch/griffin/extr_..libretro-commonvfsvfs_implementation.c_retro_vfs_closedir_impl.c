#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ directory; struct TYPE_4__* orig_path; int /*<<< orphan*/  error; } ;
typedef  TYPE_1__ libretro_vfs_implementation_dir ;

/* Variables and functions */
 int /*<<< orphan*/  FindClose (scalar_t__) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  cellFsClosedir (scalar_t__) ; 
 int /*<<< orphan*/  closedir (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  orbisDclose (scalar_t__) ; 
 int /*<<< orphan*/  ps2fileXioDclose (scalar_t__) ; 
 int /*<<< orphan*/  sceIoDclose (scalar_t__) ; 

int retro_vfs_closedir_impl(libretro_vfs_implementation_dir *rdir)
{
   if (!rdir)
      return -1;

#if defined(_WIN32)
   if (rdir->directory != INVALID_HANDLE_VALUE)
      FindClose(rdir->directory);
#elif defined(VITA) || defined(PSP)
   sceIoDclose(rdir->directory);
#elif defined(PS2)
   ps2fileXioDclose(rdir->directory);
#elif defined(__CELLOS_LV2__)
   rdir->error = cellFsClosedir(rdir->directory);
#elif defined(ORBIS)
   orbisDclose(rdir->directory);
#else
   if (rdir->directory)
      closedir(rdir->directory);
#endif

   if (rdir->orig_path)
      free(rdir->orig_path);
   free(rdir);
   return 0;
}