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

/* Variables and functions */
 int /*<<< orphan*/  MSG_COULD_NOT_FIND_VALID_DATA_TRACK ; 
 int /*<<< orphan*/  MSG_READING_FIRST_DATA_TRACK ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_LOG (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  SIZE_MAX ; 
 int /*<<< orphan*/  free (char*) ; 
 int gdi_find_track (char const*,int,char*,int) ; 
 int intfstream_file_get_serial (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int) ; 

__attribute__((used)) static int task_database_gdi_get_serial(const char *name, char* serial)
{
   char *track_path                 = (char*)malloc(PATH_MAX_LENGTH
         * sizeof(char));
   int ret                          = 0;
   int rv                           = 0;

   track_path[0]                    = '\0';

   rv = gdi_find_track(name, true, track_path, PATH_MAX_LENGTH);

   if (rv < 0)
   {
      RARCH_LOG("%s: %s\n",
            msg_hash_to_str(MSG_COULD_NOT_FIND_VALID_DATA_TRACK),
            strerror(-rv));
      free(track_path);
      return 0;
   }

   RARCH_LOG("%s\n", msg_hash_to_str(MSG_READING_FIRST_DATA_TRACK));

   ret = intfstream_file_get_serial(track_path, 0, SIZE_MAX, serial);
   free(track_path);

   return ret;
}