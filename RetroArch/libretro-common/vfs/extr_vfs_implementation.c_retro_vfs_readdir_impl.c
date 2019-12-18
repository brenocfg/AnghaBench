#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {int next; scalar_t__ directory; int /*<<< orphan*/ * entry; int /*<<< orphan*/  error; } ;
typedef  TYPE_1__ libretro_vfs_implementation_dir ;
typedef  int /*<<< orphan*/ * iox_dirent_t ;

/* Variables and functions */
 scalar_t__ FindNextFile (scalar_t__,int /*<<< orphan*/ **) ; 
 scalar_t__ FindNextFileW (scalar_t__,int /*<<< orphan*/ **) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  cellFsReaddir (scalar_t__,int /*<<< orphan*/ **,scalar_t__*) ; 
 scalar_t__ orbisDread (scalar_t__,int /*<<< orphan*/ **) ; 
 int ps2fileXioDread (scalar_t__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * readdir (scalar_t__) ; 
 scalar_t__ sceIoDread (scalar_t__,int /*<<< orphan*/ **) ; 

bool retro_vfs_readdir_impl(libretro_vfs_implementation_dir *rdir)
{
#if defined(_WIN32)
   if (rdir->next)
#if defined(LEGACY_WIN32)
      return (FindNextFile(rdir->directory, &rdir->entry) != 0);
#else
      return (FindNextFileW(rdir->directory, &rdir->entry) != 0);
#endif

   rdir->next = true;
   return (rdir->directory != INVALID_HANDLE_VALUE);
#elif defined(VITA) || defined(PSP)
   return (sceIoDread(rdir->directory, &rdir->entry) > 0);
#elif defined(PS2)
   iox_dirent_t record;
   int ret = ps2fileXioDread(rdir->directory, &record);
   rdir->entry = record;
   return ( ret > 0);
#elif defined(__CELLOS_LV2__)
   uint64_t nread;
   rdir->error = cellFsReaddir(rdir->directory, &rdir->entry, &nread);
   return (nread != 0);
#elif defined(ORBIS)
   return (orbisDread(rdir->directory, &rdir->entry) > 0);
#else
   return ((rdir->entry = readdir(rdir->directory)) != NULL);
#endif
}