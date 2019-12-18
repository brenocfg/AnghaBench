#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int ssize_t ;
typedef  int /*<<< orphan*/  libretro_vfs_implementation_file ;
struct TYPE_5__ {TYPE_1__* track; } ;
typedef  TYPE_2__ cdrom_toc_t ;
typedef  int /*<<< orphan*/  cdb ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {unsigned int lba_start; unsigned int track_size; unsigned int lba; unsigned int track_bytes; unsigned char mode; scalar_t__ audio; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIRECTION_IN ; 
 int cdrom_send_command (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,int,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned int*,unsigned char*,int) ; 
 int /*<<< orphan*/  printf (char*,unsigned int,...) ; 
 int /*<<< orphan*/  stdout ; 
 unsigned int swap_if_little32 (unsigned int) ; 

__attribute__((used)) static int cdrom_read_track_info(libretro_vfs_implementation_file *stream, unsigned char track, cdrom_toc_t *toc)
{
   /* MMC Command: READ TRACK INFORMATION */
   unsigned char cdb[] = {0x52, 0x1, 0, 0, 0, 0, 0, 0x1, 0x80, 0};
   unsigned char buf[384] = {0};
   unsigned lba = 0;
   unsigned track_size = 0;
   int rv;
   ssize_t pregap_lba_len;

   cdb[5] = track;

   rv = cdrom_send_command(stream, DIRECTION_IN, buf, sizeof(buf), cdb, sizeof(cdb), 0);

   if (rv)
     return 1;

   memcpy(&lba, buf + 8, 4);
   memcpy(&track_size, buf + 24, 4);

   lba = swap_if_little32(lba);
   track_size = swap_if_little32(track_size);

   /* lba_start may be earlier than the MSF start times seen in read_subq */
   toc->track[track - 1].lba_start = lba;
   toc->track[track - 1].track_size = track_size;

   pregap_lba_len = (toc->track[track - 1].audio ? 0 : (toc->track[track - 1].lba - toc->track[track - 1].lba_start));

   toc->track[track - 1].track_bytes = (track_size - pregap_lba_len) * 2352;
   toc->track[track - 1].mode = buf[6] & 0xF;

#ifdef CDROM_DEBUG
   printf("[CDROM] Track %d Info: ", track);
   printf("Copy: %d ", (buf[5] & 0x10) > 0);
   printf("Data Mode: %d ", toc->track[track - 1].mode);
   printf("LBA Start: %d (%d) ", lba, toc->track[track - 1].lba);
   printf("Track Size: %d\n", track_size);
   fflush(stdout);
#endif

   return 0;
}