#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  libretro_vfs_implementation_file ;
struct TYPE_6__ {unsigned char num_tracks; TYPE_1__* track; } ;
typedef  TYPE_2__ cdrom_toc_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_5__ {unsigned char track_num; unsigned char min; unsigned char sec; unsigned char frame; unsigned int lba; int audio; int mode; unsigned int lba_start; } ;

/* Variables and functions */
 unsigned char CDROM_CUE_TRACK_BYTES ; 
 scalar_t__ calloc (int,size_t) ; 
 int /*<<< orphan*/  cdrom_lba_to_msf (unsigned int,unsigned char*,unsigned char*,unsigned char*) ; 
 unsigned int cdrom_msf_to_lba (unsigned char,unsigned char,unsigned char) ; 
 int cdrom_read_subq (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  cdrom_read_track_info (int /*<<< orphan*/ *,unsigned char,TYPE_2__*) ; 
 int /*<<< orphan*/  cdrom_set_read_speed (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ snprintf (char*,size_t,char*,...) ; 
 int /*<<< orphan*/  stdout ; 

int cdrom_write_cue(libretro_vfs_implementation_file *stream, char **out_buf, size_t *out_len, char cdrom_drive, unsigned char *num_tracks, cdrom_toc_t *toc)
{
   unsigned char buf[2352] = {0};
   unsigned short data_len = 0;
   size_t len = 0;
   size_t pos = 0;
   int rv = 0;
   int i;

   if (!out_buf || !out_len || !num_tracks || !toc)
   {
#ifdef CDROM_DEBUG
      printf("[CDROM] Invalid buffer/length pointer for CDROM cue sheet\n");
      fflush(stdout);
#endif
      return 1;
   }

   cdrom_set_read_speed(stream, 0xFFFFFFFF);

   rv = cdrom_read_subq(stream, buf, sizeof(buf));

   if (rv)
      return rv;

   data_len = buf[0] << 8 | buf[1];

   for (i = 0; i < (data_len - 2) / 11; i++)
   {
      unsigned char adr = (buf[4 + (i * 11) + 1] >> 4) & 0xF;
      unsigned char tno = buf[4 + (i * 11) + 2];
      unsigned char point = buf[4 + (i * 11) + 3];
      unsigned char pmin = buf[4 + (i * 11) + 8];

      if (/*(control == 4 || control == 6) && */adr == 1 && tno == 0 && point == 0xA1)
      {
         *num_tracks = pmin;
#ifdef CDROM_DEBUG
         printf("[CDROM] Number of CDROM tracks: %d\n", *num_tracks);
         fflush(stdout);
#endif
         break;
      }
   }

   if (!*num_tracks || *num_tracks > 99)
   {
#ifdef CDROM_DEBUG
      printf("[CDROM] Invalid number of CDROM tracks: %d\n", *num_tracks);
      fflush(stdout);
#endif
      return 1;
   }

   len = CDROM_CUE_TRACK_BYTES * (*num_tracks);
   toc->num_tracks = *num_tracks;
   *out_buf = (char*)calloc(1, len);
   *out_len = len;

   for (i = 0; i < (data_len - 2) / 11; i++)
   {
      /*unsigned char session_num = buf[4 + (i * 11) + 0];*/
      unsigned char adr = (buf[4 + (i * 11) + 1] >> 4) & 0xF;
      unsigned char control = buf[4 + (i * 11) + 1] & 0xF;
      unsigned char tno = buf[4 + (i * 11) + 2];
      unsigned char point = buf[4 + (i * 11) + 3];
      /*unsigned char amin = buf[4 + (i * 11) + 4];
      unsigned char asec = buf[4 + (i * 11) + 5];
      unsigned char aframe = buf[4 + (i * 11) + 6];*/
      unsigned char pmin = buf[4 + (i * 11) + 8];
      unsigned char psec = buf[4 + (i * 11) + 9];
      unsigned char pframe = buf[4 + (i * 11) + 10];
      unsigned lba = cdrom_msf_to_lba(pmin, psec, pframe);

      /*printf("i %d control %d adr %d tno %d point %d: amin %d asec %d aframe %d pmin %d psec %d pframe %d\n", i, control, adr, tno, point, amin, asec, aframe, pmin, psec, pframe);*/
      /* why is control always 0? */

      if (/*(control == 4 || control == 6) && */adr == 1 && tno == 0 && point >= 1 && point <= 99)
      {
         bool audio = false;
         const char *track_type = "MODE1/2352";

         audio = (!(control & 0x4) && !(control & 0x5));

#ifdef CDROM_DEBUG
         printf("[CDROM] Track %02d CONTROL %01X ADR %01X AUDIO? %d\n", point, control, adr, audio);
         fflush(stdout);
#endif

         toc->track[point - 1].track_num = point;
         toc->track[point - 1].min = pmin;
         toc->track[point - 1].sec = psec;
         toc->track[point - 1].frame = pframe;
         toc->track[point - 1].lba = lba;
         toc->track[point - 1].audio = audio;

         cdrom_read_track_info(stream, point, toc);

         if (audio)
            track_type = "AUDIO";
         else if (toc->track[point - 1].mode == 1)
            track_type = "MODE1/2352";
         else if (toc->track[point - 1].mode == 2)
            track_type = "MODE2/2352";

#if defined(_WIN32) && !defined(_XBOX)
         pos += snprintf(*out_buf + pos, len - pos, "FILE \"cdrom://%c:/drive-track%02d.bin\" BINARY\n", cdrom_drive, point);
#else
         pos += snprintf(*out_buf + pos, len - pos, "FILE \"cdrom://drive%c-track%02d.bin\" BINARY\n", cdrom_drive, point);
#endif
         pos += snprintf(*out_buf + pos, len - pos, "  TRACK %02d %s\n", point, track_type);

         {
            unsigned pregap_lba_len = toc->track[point - 1].lba - toc->track[point - 1].lba_start;

            if (toc->track[point - 1].audio && pregap_lba_len > 0)
            {
               unsigned char min = 0;
               unsigned char sec = 0;
               unsigned char frame = 0;

               cdrom_lba_to_msf(pregap_lba_len, &min, &sec, &frame);

               pos += snprintf(*out_buf + pos, len - pos, "    INDEX 00 00:00:00\n");
               pos += snprintf(*out_buf + pos, len - pos, "    INDEX 01 %02u:%02u:%02u\n", (unsigned)min, (unsigned)sec, (unsigned)frame);
            }
            else
               pos += snprintf(*out_buf + pos, len - pos, "    INDEX 01 00:00:00\n");
         }
      }
   }

   return 0;
}