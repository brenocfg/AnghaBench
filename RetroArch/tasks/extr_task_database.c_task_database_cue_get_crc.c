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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_COULD_NOT_FIND_VALID_DATA_TRACK ; 
 int /*<<< orphan*/  MSG_READING_FIRST_DATA_TRACK ; 
 int /*<<< orphan*/  PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_LOG (char*,char const*,...) ; 
 int cue_find_track (char const*,int,scalar_t__*,scalar_t__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int intfstream_file_get_crc (char*,scalar_t__,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 
 char const* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int) ; 

__attribute__((used)) static int task_database_cue_get_crc(const char *name, uint32_t *crc)
{
   char *track_path = (char *)malloc(PATH_MAX_LENGTH);
   uint64_t offset  = 0;
   uint64_t size    = 0;
   int rv           = 0;

   track_path[0]    = '\0';

   rv = cue_find_track(name, false, &offset, &size,
         track_path, PATH_MAX_LENGTH);

   if (rv < 0)
   {
      RARCH_LOG("%s: %s\n",
            msg_hash_to_str(MSG_COULD_NOT_FIND_VALID_DATA_TRACK),
            strerror(-rv));
      free(track_path);
      return 0;
   }

   RARCH_LOG("CUE '%s' primary track: %s\n (%lu, %lu)\n",name, track_path, (unsigned long) offset, (unsigned long) size);

   RARCH_LOG("%s\n", msg_hash_to_str(MSG_READING_FIRST_DATA_TRACK));

   rv = intfstream_file_get_crc(track_path, offset, (size_t)size, crc);
   if (rv == 1)
   {
      RARCH_LOG("CUE '%s' crc: %x\n", name, *crc);
   }
   free(track_path);
   return rv;
}