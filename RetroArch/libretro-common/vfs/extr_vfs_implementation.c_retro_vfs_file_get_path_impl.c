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
struct TYPE_3__ {char const* orig_path; } ;
typedef  TYPE_1__ libretro_vfs_implementation_file ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 

const char *retro_vfs_file_get_path_impl(
      libretro_vfs_implementation_file *stream)
{
   /* should never happen, do something noisy so caller can be fixed */
   if (!stream)
      abort();
   return stream->orig_path;
}