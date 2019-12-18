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

/* Variables and functions */
 int /*<<< orphan*/  MAX_TOKEN_LEN ; 
 int /*<<< orphan*/  PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  fill_pathname_basedir (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_pathname_join (char*,char*,char*,size_t) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ get_token (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 
 scalar_t__ string_is_equal_noncase (char*,char*) ; 

bool cue_next_file(intfstream_t *fd,
      const char *cue_path, char *path, uint64_t max_len)
{
   bool rv                    = false;
   char *tmp_token            = (char*)malloc(MAX_TOKEN_LEN);
   char *cue_dir              = (char*)malloc(PATH_MAX_LENGTH);
   cue_dir[0]                 = '\0';

   fill_pathname_basedir(cue_dir, cue_path, PATH_MAX_LENGTH);

   tmp_token[0] = '\0';

   while (get_token(fd, tmp_token, MAX_TOKEN_LEN) > 0)
   {
      if (string_is_equal_noncase(tmp_token, "FILE"))
      {
         get_token(fd, tmp_token, MAX_TOKEN_LEN);
         fill_pathname_join(path, cue_dir, tmp_token, (size_t)max_len);
         rv = true;
         break;
      }
   }

   free(cue_dir);
   free(tmp_token);
   return rv;
}