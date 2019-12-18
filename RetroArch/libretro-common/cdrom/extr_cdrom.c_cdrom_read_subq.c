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
 int /*<<< orphan*/  DIRECTION_IN ; 
 int cdrom_send_command (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,size_t,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 

int cdrom_read_subq(libretro_vfs_implementation_file *stream, unsigned char *buf, size_t len)
{
   /* MMC Command: READ TOC/PMA/ATIP */
   unsigned char cdb[] = {0x43, 0x2, 0x2, 0, 0, 0, 0x1, 0x9, 0x30, 0};
#ifdef CDROM_DEBUG
   unsigned short data_len = 0;
   unsigned char first_session = 0;
   unsigned char last_session = 0;
   int i;
#endif
   int rv;

   if (!buf)
      return 1;

   rv = cdrom_send_command(stream, DIRECTION_IN, buf, len, cdb, sizeof(cdb), 0);

   if (rv)
     return 1;

#ifdef CDROM_DEBUG
   data_len = buf[0] << 8 | buf[1];
   first_session = buf[2];
   last_session = buf[3];

   printf("[CDROM] Data Length: %d\n", data_len);
   printf("[CDROM] First Session: %d\n", first_session);
   printf("[CDROM] Last Session: %d\n", last_session);

   for (i = 0; i < (data_len - 2) / 11; i++)
   {
      unsigned char session_num = buf[4 + (i * 11) + 0];
      unsigned char adr = (buf[4 + (i * 11) + 1] >> 4) & 0xF;
      /*unsigned char control = buf[4 + (i * 11) + 1] & 0xF;*/
      unsigned char tno = buf[4 + (i * 11) + 2];
      unsigned char point = buf[4 + (i * 11) + 3];
      unsigned char pmin = buf[4 + (i * 11) + 8];
      unsigned char psec = buf[4 + (i * 11) + 9];
      unsigned char pframe = buf[4 + (i * 11) + 10];

      /*printf("i %d control %d adr %d tno %d point %d: ", i, control, adr, tno, point);*/
      /* why is control always 0? */

      if (/*(control == 4 || control == 6) && */adr == 1 && tno == 0 && point >= 1 && point <= 99)
      {
         printf("[CDROM] - Session#: %d TNO %d POINT %d ", session_num, tno, point);
         printf("Track start time: (aMSF %02u:%02u:%02u) ", (unsigned)pmin, (unsigned)psec, (unsigned)pframe);
      }
      else if (/*(control == 4 || control == 6) && */adr == 1 && tno == 0 && point == 0xA0)
      {
         printf("[CDROM] - Session#: %d TNO %d POINT %d ", session_num, tno, point);
         printf("First Track Number: %d ", pmin);
         printf("Disc Type: %d ", psec);
      }
      else if (/*(control == 4 || control == 6) && */adr == 1 && tno == 0 && point == 0xA1)
      {
         printf("[CDROM] - Session#: %d TNO %d POINT %d ", session_num, tno, point);
         printf("Last Track Number: %d ", pmin);
      }
      else if (/*(control == 4 || control == 6) && */adr == 1 && tno == 0 && point == 0xA2)
      {
         printf("[CDROM] - Session#: %d TNO %d POINT %d ", session_num, tno, point);
         printf("Lead-out start time: (aMSF %02u:%02u:%02u) ", (unsigned)pmin, (unsigned)psec, (unsigned)pframe);
      }

      printf("\n");
   }

   fflush(stdout);
#endif
   return 0;
}