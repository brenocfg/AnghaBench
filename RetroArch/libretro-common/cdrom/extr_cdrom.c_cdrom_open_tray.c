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
 int /*<<< orphan*/  cdrom_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cdrom_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  stdout ; 

int cdrom_open_tray(libretro_vfs_implementation_file *stream)
{
   /* MMC Command: START STOP UNIT */
   unsigned char cdb[] = {0x1B, 0, 0, 0, 0x2, 0};
   int rv;

   cdrom_unlock(stream);
   cdrom_stop(stream);

   rv = cdrom_send_command(stream, DIRECTION_NONE, NULL, 0, cdb, sizeof(cdb), 0);

#ifdef CDROM_DEBUG
   printf("[CDROM] open tray status code %d\n", rv);
   fflush(stdout);
#endif

   if (rv)
      return 1;

   return 0;
}