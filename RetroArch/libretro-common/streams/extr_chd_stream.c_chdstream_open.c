#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_8__ {char* pgtype; scalar_t__ frames; int /*<<< orphan*/  frame_offset; scalar_t__ pregap; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ metadata_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_9__ {int frame_size; int swab; int frames_per_hunk; size_t track_start; size_t track_end; int hunknum; scalar_t__ offset; int /*<<< orphan*/  track_frame; int /*<<< orphan*/ * chd; scalar_t__ frame_offset; int /*<<< orphan*/ * hunkmem; } ;
typedef  TYPE_2__ chdstream_t ;
struct TYPE_10__ {int hunkbytes; int unitbytes; } ;
typedef  TYPE_3__ chd_header ;
typedef  int /*<<< orphan*/  chd_file ;
typedef  scalar_t__ chd_error ;

/* Variables and functions */
 scalar_t__ CHDERR_NONE ; 
 int /*<<< orphan*/  CHD_OPEN_READ ; 
 void* SECTOR_SIZE ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  chd_close (int /*<<< orphan*/ *) ; 
 TYPE_3__* chd_get_header (int /*<<< orphan*/ *) ; 
 scalar_t__ chd_open (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  chdstream_close (TYPE_2__*) ; 
 int /*<<< orphan*/  chdstream_find_track (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

chdstream_t *chdstream_open(const char *path, int32_t track)
{
   metadata_t meta;
   uint32_t pregap      = 0;
   const chd_header *hd = NULL;
   chdstream_t *stream  = NULL;
   chd_file *chd        = NULL;
   chd_error err        = chd_open(path, CHD_OPEN_READ, NULL, &chd);

   if (err != CHDERR_NONE)
      goto error;

   if (!chdstream_find_track(chd, track, &meta))
      goto error;

   stream = (chdstream_t*)calloc(1, sizeof(*stream));
   if (!stream)
      goto error;

   hd              = chd_get_header(chd);
   stream->hunkmem = (uint8_t*)malloc(hd->hunkbytes);
   if (!stream->hunkmem)
      goto error;

   if (!strcmp(meta.type, "MODE1_RAW"))
   {
      stream->frame_size = SECTOR_SIZE;
      stream->frame_offset = 0;
   }
   else if (!strcmp(meta.type, "MODE2_RAW"))
   {
      stream->frame_size = SECTOR_SIZE;
      stream->frame_offset = 0;
   }
   else if (!strcmp(meta.type, "AUDIO"))
   {
      stream->frame_size = SECTOR_SIZE;
      stream->frame_offset = 0;
      stream->swab = true;
   }
   else
   {
      stream->frame_size = hd->unitbytes;
      stream->frame_offset = 0;
   }

   /* Only include pregap data if it was in the track file */
   if (!strcmp(meta.type, meta.pgtype))
      pregap = meta.pregap;
   else
      pregap = 0;

   stream->chd             = chd;
   stream->frames_per_hunk = hd->hunkbytes / hd->unitbytes;
   stream->track_frame     = meta.frame_offset;
   stream->track_start     = (size_t) pregap * stream->frame_size;
   stream->track_end       = stream->track_start +
      (size_t) meta.frames * stream->frame_size;
   stream->offset          = 0;
   stream->hunknum         = -1;

   return stream;

error:

   chdstream_close(stream);

   if (chd)
      chd_close(chd);

   return NULL;
}