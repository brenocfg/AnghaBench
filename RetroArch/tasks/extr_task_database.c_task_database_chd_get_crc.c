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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  intfstream_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHDSTREAM_TRACK_PRIMARY ; 
 int /*<<< orphan*/  RARCH_LOG (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RETRO_VFS_FILE_ACCESS_HINT_NONE ; 
 int /*<<< orphan*/  RETRO_VFS_FILE_ACCESS_READ ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intfstream_close (int /*<<< orphan*/ *) ; 
 int intfstream_get_crc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * intfstream_open_chd_track (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool task_database_chd_get_crc(const char *name, uint32_t *crc)
{
   int rv;
   intfstream_t *fd = intfstream_open_chd_track(
         name,
         RETRO_VFS_FILE_ACCESS_READ,
         RETRO_VFS_FILE_ACCESS_HINT_NONE,
         CHDSTREAM_TRACK_PRIMARY);
   if (!fd)
      return 0;

   rv = intfstream_get_crc(fd, crc);
   if (rv == 1)
   {
      RARCH_LOG("CHD '%s' crc: %x\n", name, *crc);
   }
   if (fd)
   {
      intfstream_close(fd);
      free(fd);
   }
   return rv;
}