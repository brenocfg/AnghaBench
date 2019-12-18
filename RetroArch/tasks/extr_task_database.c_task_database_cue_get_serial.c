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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_COULD_NOT_FIND_VALID_DATA_TRACK ; 
 int /*<<< orphan*/  MSG_READING_FIRST_DATA_TRACK ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_LOG (char*,int /*<<< orphan*/ ,...) ; 
 int cue_find_track (char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int intfstream_file_get_serial (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int) ; 

__attribute__((used)) static int task_database_cue_get_serial(const char *name, char* serial)
{
   char *track_path                 = (char*)malloc(PATH_MAX_LENGTH
         * sizeof(char));
   int ret                          = 0;
   uint64_t offset                  = 0;
   uint64_t size                    = 0;
   int rv                           = 0;

   track_path[0]                    = '\0';

   rv = cue_find_track(name, true, &offset, &size, track_path, PATH_MAX_LENGTH);

   if (rv < 0)
   {
      RARCH_LOG("%s: %s\n",
            msg_hash_to_str(MSG_COULD_NOT_FIND_VALID_DATA_TRACK),
            strerror(-rv));
      free(track_path);
      return 0;
   }

   RARCH_LOG("%s\n", msg_hash_to_str(MSG_READING_FIRST_DATA_TRACK));

   ret = intfstream_file_get_serial(track_path, offset, size, serial);
   free(track_path);

   return ret;
}