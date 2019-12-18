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
struct TYPE_3__ {scalar_t__ directory; scalar_t__ error; } ;
typedef  TYPE_1__ libretro_vfs_implementation_dir ;

/* Variables and functions */
 scalar_t__ CELL_FS_SUCCEEDED ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 

__attribute__((used)) static bool dirent_check_error(libretro_vfs_implementation_dir *rdir)
{
#if defined(_WIN32)
   return (rdir->directory == INVALID_HANDLE_VALUE);
#elif defined(VITA) || defined(PSP) || defined(PS2) || defined(ORBIS)
   return (rdir->directory < 0);
#elif defined(__CELLOS_LV2__)
   return (rdir->error != CELL_FS_SUCCEEDED);
#else
   return !(rdir->directory);
#endif
}