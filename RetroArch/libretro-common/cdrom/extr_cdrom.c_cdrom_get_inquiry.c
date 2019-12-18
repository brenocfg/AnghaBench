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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  DIRECTION_IN ; 
 int cdrom_send_command (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,int,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 

int cdrom_get_inquiry(libretro_vfs_implementation_file *stream, char *model, int len, bool *is_cdrom)
{
   /* MMC Command: INQUIRY */
   unsigned char cdb[] = {0x12, 0, 0, 0, 0xff, 0};
   unsigned char buf[256] = {0};
   int rv = cdrom_send_command(stream, DIRECTION_IN, buf, sizeof(buf), cdb, sizeof(cdb), 0);
   bool cdrom = false;

   if (rv)
      return 1;

   if (model && len >= 32)
   {
      memset(model, 0, len);

      /* vendor */
      memcpy(model, buf + 8, 8);

      model[8] = ' ';

      /* product */
      memcpy(model + 9, buf + 16, 16);

      model[25] = ' ';

      /* version */
      memcpy(model + 26, buf + 32, 4);
   }

   cdrom = (buf[0] == 5);

   if (is_cdrom && cdrom)
      *is_cdrom = true;

#ifdef CDROM_DEBUG
   printf("[CDROM] Device Model: %s (is CD-ROM? %s)\n", model, (cdrom ? "yes" : "no"));
#endif
   return 0;
}