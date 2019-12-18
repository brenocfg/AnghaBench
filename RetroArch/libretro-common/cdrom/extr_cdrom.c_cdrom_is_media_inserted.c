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
typedef  int /*<<< orphan*/  cdb ;

/* Variables and functions */
 int /*<<< orphan*/  DIRECTION_NONE ; 
 int cdrom_send_command (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  stdout ; 

bool cdrom_is_media_inserted(libretro_vfs_implementation_file *stream)
{
   /* MMC Command: TEST UNIT READY */
   unsigned char cdb[] = {0x00, 0, 0, 0, 0, 0};
   int rv = cdrom_send_command(stream, DIRECTION_NONE, NULL, 0, cdb, sizeof(cdb), 0);

#ifdef CDROM_DEBUG
   printf("[CDROM] media inserted status code %d\n", rv);
   fflush(stdout);
#endif

   /* Will also return false if the drive is simply not ready yet (tray open, disc spinning back up after tray closed etc).
    * Command will not block or wait for media to become ready. */
   if (rv)
      return false;

   return true;
}