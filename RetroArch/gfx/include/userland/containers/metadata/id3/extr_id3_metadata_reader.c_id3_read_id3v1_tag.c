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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  track_num ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;

/* Variables and functions */
 scalar_t__ READ_U8 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SKIP_BYTES (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SKIP_STRING (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  STREAM_STATUS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VC_CONTAINER_METADATA_KEY_ALBUM ; 
 int /*<<< orphan*/  VC_CONTAINER_METADATA_KEY_ARTIST ; 
 int /*<<< orphan*/  VC_CONTAINER_METADATA_KEY_GENRE ; 
 int /*<<< orphan*/  VC_CONTAINER_METADATA_KEY_TITLE ; 
 int /*<<< orphan*/  VC_CONTAINER_METADATA_KEY_TRACK ; 
 int /*<<< orphan*/  VC_CONTAINER_METADATA_KEY_YEAR ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int countof (char**) ; 
 int /*<<< orphan*/  id3_add_metadata_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 char** id3_genres ; 
 int /*<<< orphan*/  id3_read_metadata_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T id3_read_id3v1_tag( VC_CONTAINER_T *p_ctx )
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   uint8_t track, genre;
   char track_num[4] = {0};

   SKIP_STRING(p_ctx, 3, "ID3v1 identifier");
   /* ID3v1 title */
   id3_read_metadata_entry(p_ctx, VC_CONTAINER_METADATA_KEY_TITLE, 30);
   /* ID3v1 artist */
   id3_read_metadata_entry(p_ctx, VC_CONTAINER_METADATA_KEY_ARTIST, 30);
   /* ID3v1 album */
   id3_read_metadata_entry(p_ctx, VC_CONTAINER_METADATA_KEY_ALBUM, 30);
   /* ID3v1 year */
   id3_read_metadata_entry(p_ctx, VC_CONTAINER_METADATA_KEY_YEAR, 4);
   SKIP_STRING(p_ctx, 28, "ID3v1 comment");
   if (READ_U8(p_ctx, "ID3v1 zero-byte") == 0)
   {
      track = READ_U8(p_ctx, "ID3v1 track");
      snprintf(track_num, sizeof(track_num) - 1, "%02d", track);
      id3_add_metadata_entry(p_ctx, VC_CONTAINER_METADATA_KEY_TRACK, track_num);
   }
   else
   {
      SKIP_BYTES(p_ctx, 1);
   }
   genre = READ_U8(p_ctx, "ID3v1 genre");
   if (genre < countof(id3_genres))
   {
      id3_add_metadata_entry(p_ctx, VC_CONTAINER_METADATA_KEY_GENRE, id3_genres[genre]);
   }

   status = STREAM_STATUS(p_ctx);

   return status;
}