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
typedef  char* uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_COULD_NOT_FIND_VALID_DATA_TRACK ; 
 int /*<<< orphan*/  MSG_READING_FIRST_DATA_TRACK ; 
 int /*<<< orphan*/  PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_LOG (char*,char const*,...) ; 
 int /*<<< orphan*/  SIZE_MAX ; 
 int /*<<< orphan*/  free (char*) ; 
 int gdi_find_track (char const*,int,char*,int /*<<< orphan*/ ) ; 
 int intfstream_file_get_crc (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 
 char const* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 char* strerror (int) ; 

__attribute__((used)) static int task_database_gdi_get_crc(const char *name, uint32_t *crc)
{
   char *track_path = (char *)malloc(PATH_MAX_LENGTH);
   int rv           = 0;

   track_path[0] = '\0';

   rv = gdi_find_track(name, true, track_path, PATH_MAX_LENGTH);

   if (rv < 0)
   {
      RARCH_LOG("%s: %s\n", msg_hash_to_str(MSG_COULD_NOT_FIND_VALID_DATA_TRACK),
                strerror(-rv));
      free(track_path);
      return 0;
   }

   RARCH_LOG("GDI '%s' primary track: %s\n", name, track_path);

   RARCH_LOG("%s\n", msg_hash_to_str(MSG_READING_FIRST_DATA_TRACK));

   rv = intfstream_file_get_crc(track_path, 0, SIZE_MAX, crc);
   if (rv == 1)
   {
      RARCH_LOG("GDI '%s' crc: %x\n", name, *crc);
   }
   free(track_path);
   return rv;
}