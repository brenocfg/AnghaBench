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
struct TYPE_3__ {int /*<<< orphan*/  fp; } ;
typedef  TYPE_1__ libretro_vfs_implementation_file ;

/* Variables and functions */
 scalar_t__ fflush (int /*<<< orphan*/ ) ; 

int retro_vfs_file_flush_impl(libretro_vfs_implementation_file *stream)
{
   if (!stream)
      return -1;
#ifdef ORBIS
   return 0;
#else
   return fflush(stream->fp) == 0 ? 0 : -1;
#endif
}