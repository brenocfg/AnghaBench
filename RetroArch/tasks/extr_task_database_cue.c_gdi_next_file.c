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
typedef  int /*<<< orphan*/  intfstream_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_TOKEN_LEN ; 
 int /*<<< orphan*/  PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  fill_pathname_basedir (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_pathname_join (char*,char*,char*,size_t) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ get_token (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ intfstream_tell (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 

bool gdi_next_file(intfstream_t *fd, const char *gdi_path,
      char *path, uint64_t max_len)
{
   bool rv         = false;
   char *tmp_token = (char*)malloc(MAX_TOKEN_LEN);
   int64_t offset  = -1;

   tmp_token[0]    = '\0';

   /* Skip initial track count */
   offset = intfstream_tell(fd);
   if (offset == 0)
      get_token(fd, tmp_token, MAX_TOKEN_LEN);

   /* Track number */
   get_token(fd, tmp_token, MAX_TOKEN_LEN);

   /* Offset */
   get_token(fd, tmp_token, MAX_TOKEN_LEN);

   /* Mode */
   get_token(fd, tmp_token, MAX_TOKEN_LEN);

   /* Sector size */
   get_token(fd, tmp_token, MAX_TOKEN_LEN);

   /* File name */
   if (get_token(fd, tmp_token, MAX_TOKEN_LEN) > 0)
   {
      char *gdi_dir   = (char*)malloc(PATH_MAX_LENGTH);

      gdi_dir[0]      = '\0';

      fill_pathname_basedir(gdi_dir, gdi_path, PATH_MAX_LENGTH);

      fill_pathname_join(path, gdi_dir, tmp_token, (size_t)max_len);
      rv = true;

      /* Disc offset */
      get_token(fd, tmp_token, MAX_TOKEN_LEN);

      free(gdi_dir);
   }

   free(tmp_token);
   return rv;
}