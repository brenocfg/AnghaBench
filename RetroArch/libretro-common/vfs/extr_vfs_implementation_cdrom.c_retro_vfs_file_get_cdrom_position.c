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
typedef  int /*<<< orphan*/  vfs_cdrom_t ;
struct TYPE_3__ {int /*<<< orphan*/  const cdrom; } ;
typedef  TYPE_1__ libretro_vfs_implementation_file ;

/* Variables and functions */

const vfs_cdrom_t* retro_vfs_file_get_cdrom_position(const libretro_vfs_implementation_file *stream)
{
   return &stream->cdrom;
}