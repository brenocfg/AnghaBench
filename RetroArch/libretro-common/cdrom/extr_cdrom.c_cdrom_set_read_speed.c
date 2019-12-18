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
typedef  int /*<<< orphan*/  libretro_vfs_implementation_file ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  DIRECTION_NONE ; 
 int cdrom_send_command (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ ) ; 

int cdrom_set_read_speed(libretro_vfs_implementation_file *stream, unsigned speed)
{
   /* MMC Command: SET CD SPEED */
   unsigned char cmd[] = {0xBB, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

   cmd[2] = (speed >> 24) & 0xFF;
   cmd[3] = (speed >> 16) & 0xFF;
   cmd[4] = (speed >> 8) & 0xFF;
   cmd[5] = speed & 0xFF;

   return cdrom_send_command(stream, DIRECTION_NONE, NULL, 0, cmd, sizeof(cmd), 0);
}