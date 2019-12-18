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
 int /*<<< orphan*/  printf (char*,...) ; 

void cdrom_get_current_config_cdread(libretro_vfs_implementation_file *stream)
{
   unsigned char cdb[] = {0x46, 0x2, 0, 0x1E, 0, 0, 0, 0, 0x10, 0};
   unsigned char buf[0x10] = {0};
   int rv = cdrom_send_command(stream, DIRECTION_IN, buf, sizeof(buf), cdb, sizeof(cdb), 0);
   int i;

   printf("[CDROM] get current config cd read status code %d\n", rv);

   if (rv)
      return;

   printf("[CDROM] Feature Header: ");

   for (i = 0; i < 8; i++)
   {
      printf("%02X ", buf[i]);
   }

   printf("\n");

   printf("[CDROM] CD Read Feature Descriptor: ");

   for (i = 0; i < 8; i++)
   {
      printf("%02X ", buf[8 + i]);
   }

   if (buf[8 + 2] & 1)
      printf("(current)\n");

   printf("[CDROM] Supported commands: READ CD, READ CD MSF, READ TOC/PMA/ATIP\n");
}