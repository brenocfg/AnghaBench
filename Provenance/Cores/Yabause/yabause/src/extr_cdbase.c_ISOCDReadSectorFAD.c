#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct TYPE_4__ {scalar_t__ fad_start; scalar_t__ fad_end; int file_offset; scalar_t__ sector_size; scalar_t__ fp; scalar_t__ sub_fp; int /*<<< orphan*/  interleaved_sub; } ;
typedef  TYPE_1__ track_info_struct ;
struct TYPE_6__ {int track_num; TYPE_1__* track; } ;
struct TYPE_5__ {int session_num; TYPE_3__* session; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDLOG (char*) ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 TYPE_2__ disc ; 
 size_t fread (char*,int,int,scalar_t__) ; 
 int /*<<< orphan*/  fseek (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  syncHdr ; 

__attribute__((used)) static int ISOCDReadSectorFAD(u32 FAD, void *buffer) {
   int i,j;
   size_t num_read = 0;
   track_info_struct *track=NULL;

   assert(disc.session);

   memset(buffer, 0, 2448);

   for (i = 0; i < disc.session_num; i++)
   {
      for (j = 0; j < disc.session[i].track_num; j++)
      {
         if (FAD >= disc.session[i].track[j].fad_start &&
             FAD <= disc.session[i].track[j].fad_end)
         {             
            track = &disc.session[i].track[j];
            break;
         }
      }
   }

   if (track == NULL)
   {
      CDLOG("Warning: Sector not found in track list");
      return 0;
   }

   fseek(track->fp, track->file_offset + (FAD-track->fad_start) * track->sector_size, SEEK_SET);
	if (track->sub_fp)
		fseek(track->sub_fp, track->file_offset + (FAD-track->fad_start) * 96, SEEK_SET);
   if (track->sector_size == 2448)
   {
      if (!track->interleaved_sub)
		{
			if (track->sub_fp)
			{
            num_read = fread(buffer, 2352, 1, track->fp);
            num_read = fread((char *)buffer + 2352, 96, 1, track->sub_fp);
			}
			else
            num_read = fread(buffer, 2448, 1, track->fp);
		}
      else
      {
         const u16 deint_offsets[] = {
            0, 66, 125, 191, 100, 50, 150, 175, 8, 33, 58, 83, 
            108, 133, 158, 183, 16, 41, 25, 91, 116, 141, 166, 75, 
            24, 90, 149, 215, 124, 74, 174, 199, 32, 57, 82, 107, 
            132, 157, 182, 207, 40, 65, 49, 115, 140, 165, 190, 99, 
            48, 114, 173, 239, 148, 98, 198, 223, 56, 81, 106, 131, 
            156, 181, 206, 231, 64, 89, 73, 139, 164, 189, 214, 123, 
            72, 138, 197, 263, 172, 122, 222, 247, 80, 105, 130, 155, 
            180, 205, 230, 255, 88, 113, 97, 163, 188, 213, 238, 147
         };
         u8 subcode_buffer[96 * 3];

         num_read = fread(buffer, 2352, 1, track->fp);

         num_read = fread(subcode_buffer, 96, 1, track->fp);
         fseek(track->fp, 2352, SEEK_CUR);
         num_read = fread(subcode_buffer + 96, 96, 1, track->fp);
         fseek(track->fp, 2352, SEEK_CUR);
         num_read = fread(subcode_buffer + 192, 96, 1, track->fp);
         for (i = 0; i < 96; i++)
            ((u8 *)buffer)[2352+i] = subcode_buffer[deint_offsets[i]];
      }
   }
   else if (track->sector_size == 2352)
   {
      // Generate subcodes here
      num_read = fread(buffer, 2352, 1, track->fp);
   }
   else if (track->sector_size == 2048)
   {
      memcpy(buffer, syncHdr, 12);
      num_read = fread((char *)buffer + 0x10, 2048, 1, track->fp);
   }
	return 1;
}