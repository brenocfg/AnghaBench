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
 int /*<<< orphan*/  printf (char*,unsigned short,unsigned char,unsigned char) ; 

bool cdrom_has_atip(libretro_vfs_implementation_file *stream)
{
   /* MMC Command: READ TOC/PMA/ATIP */
   unsigned char cdb[] = {0x43, 0x2, 0x4, 0, 0, 0, 0, 0x9, 0x30, 0};
   unsigned char buf[32] = {0};
   unsigned short atip_len = 0;
   int rv = cdrom_send_command(stream, DIRECTION_IN, buf, sizeof(buf), cdb, sizeof(cdb), 0);

   if (rv)
     return false;

   atip_len = buf[0] << 8 | buf[1];

#ifdef CDROM_DEBUG
   printf("ATIP Length %d, Disc Type %d, Disc Sub-Type %d\n", atip_len, (buf[6] >> 6) & 0x1, ((buf[6] >> 5) & 0x1) << 2 | ((buf[6] >> 4) & 0x1) << 1 | ((buf[6] >> 3) & 0x1) << 0);
#endif

   if (atip_len < 5)
      return false;

   return true;
}