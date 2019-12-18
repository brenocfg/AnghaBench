#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  intfstream_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_2__ {char* system_name; int offset; int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAGIC_LEN ; 
 TYPE_1__* MAGIC_NUMBERS ; 
 int /*<<< orphan*/  MSG_COMPARING_WITH_KNOWN_MAGIC_NUMBERS ; 
 int /*<<< orphan*/  MSG_COULD_NOT_FIND_COMPATIBLE_SYSTEM ; 
 int /*<<< orphan*/  RARCH_LOG (char*,int,...) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int errno ; 
 scalar_t__ intfstream_read (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  intfstream_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  string_is_empty (char*) ; 
 scalar_t__ string_is_equal (char*,char*) ; 

int detect_system(intfstream_t *fd, const char **system_name)
{
   int rv;
   char magic[MAGIC_LEN];
   int i;
   int64_t read;

   RARCH_LOG("%s\n", msg_hash_to_str(MSG_COMPARING_WITH_KNOWN_MAGIC_NUMBERS));
   for (i = 0; MAGIC_NUMBERS[i].system_name != NULL; i++)
   {
      intfstream_seek(fd, MAGIC_NUMBERS[i].offset, SEEK_SET);

      read = intfstream_read(fd, magic, MAGIC_LEN);
      if (read < 0)
      {
         RARCH_LOG("Could not read data at offset %d: %s\n",
               MAGIC_NUMBERS[i].offset, strerror(errno));
         rv = -errno;
         goto clean;
      }

      if (read < MAGIC_LEN)
         continue;

      if (memcmp(MAGIC_NUMBERS[i].magic, magic, MAGIC_LEN) == 0)
      {
         *system_name = MAGIC_NUMBERS[i].system_name;
         rv = 0;
         goto clean;
      }
   }

   intfstream_seek(fd, 0x8008, SEEK_SET);
   if (intfstream_read(fd, magic, 8) > 0)
   {
      magic[8] = '\0';
      if (!string_is_empty(magic) &&
            string_is_equal(magic, "PSP GAME"))
      {
         *system_name = "psp\0";
         rv = 0;
         goto clean;
      }
   }

   RARCH_LOG("%s\n", msg_hash_to_str(MSG_COULD_NOT_FIND_COMPATIBLE_SYSTEM));
   rv = -EINVAL;

clean:
   return rv;
}