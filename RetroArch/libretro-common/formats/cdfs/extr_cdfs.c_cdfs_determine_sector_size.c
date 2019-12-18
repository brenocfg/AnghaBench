#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int int64_t ;
struct TYPE_3__ {int pregap_sectors; int stream_sector_size; int stream_sector_header_size; int /*<<< orphan*/  stream; } ;
typedef  TYPE_1__ cdfs_track_t ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int intfstream_get_size (int /*<<< orphan*/ ) ; 
 int intfstream_read (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  intfstream_seek (int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cdfs_determine_sector_size(cdfs_track_t* track)
{
   uint8_t buffer[32];
   int64_t stream_size;
   const int toc_sector = track->pregap_sectors + 16;

   /* MODE information is normally found in the CUE sheet, but we can try to determine it from the raw data.
    *
    *   MODE1/2048 - CDROM Mode1 Data (cooked) [no header, no footer]
    *   MODE1/2352 - CDROM Mode1 Data (raw)    [16 byte header, 288 byte footer]
    *   MODE2/2336 - CDROM-XA Mode2 Data       [8 byte header, 280 byte footer]
    *   MODE2/2352 - CDROM-XA Mode2 Data       [24 byte header, 280 byte footer]
    *
    * Note that MODE is actually a property on each sector and can change between 1 and 2 depending on how much error
    * correction the author desired. To support that, the data format must be "/2352" to include the full header and
    * data without error correction information, at which point the CUE sheet information becomes just a hint.
    */

   /* The boot record or primary volume descriptor is always at sector 16 and will contain a "CD001" marker */
   intfstream_seek(track->stream, toc_sector * 2352, SEEK_SET);
   if (intfstream_read(track->stream, buffer, sizeof(buffer)) < sizeof(buffer))
      return;

   /* if this is a CDROM-XA data source, the "CD001" tag will be 25 bytes into the sector */
   if (buffer[25] == 0x43 && buffer[26] == 0x44 &&
      buffer[27] == 0x30 && buffer[28] == 0x30 && buffer[29] == 0x31)
   {
      track->stream_sector_size = 2352;
      track->stream_sector_header_size = 24;
   }
   /* otherwise it should be 17 bytes into the sector */
   else if (buffer[17] == 0x43 && buffer[18] == 0x44 &&
      buffer[19] == 0x30 && buffer[20] == 0x30 && buffer[21] == 0x31)
   {
      track->stream_sector_size = 2352;
      track->stream_sector_header_size = 16;
   }
   else
   {
      /* ISO-9660 says the first twelve bytes of a sector should be the sync pattern 00 FF FF FF FF FF FF FF FF FF FF 00 */
      if (buffer[0] == 0 && buffer[1] == 0xFF && buffer[2] == 0xFF && buffer[3] == 0xFF &&
         buffer[4] == 0xFF && buffer[5] == 0xFF && buffer[6] == 0xFF && buffer[7] == 0xFF &&
         buffer[8] == 0xFF && buffer[9] == 0xFF && buffer[10] == 0xFF && buffer[11] == 0)
      {
         /* if we didn't find a CD001 tag, this format may predate ISO-9660 */

         /* after the 12 byte sync pattern is three bytes identifying the sector and then one byte for the mode (total 16 bytes) */
         track->stream_sector_size = 2352;
         track->stream_sector_header_size = 16;
      }
      else
      {
         /* no recognizable header - attempt to determine sector size from stream size */
         stream_size = intfstream_get_size(track->stream);

         if ((stream_size % 2352) == 0)
         {
            /* audio tracks use all 2352 bytes without a header */
            track->stream_sector_size = 2352;
         }
         else if ((stream_size % 2048) == 0)
         {
            /* cooked tracks eliminate all header/footer data */
            track->stream_sector_size = 2048;
         }
         else if ((stream_size % 2336) == 0)
         {
            /* MODE 2 format without 16-byte sync data */
            track->stream_sector_size = 2336;
            track->stream_sector_header_size = 8;
         }
      }
   }
}