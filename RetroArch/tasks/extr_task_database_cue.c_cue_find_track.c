#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  char intfstream_t ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ intfstream_info_t ;
typedef  int int64_t ;
typedef  int int32_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INTFSTREAM_FILE ; 
 scalar_t__ MAX_TOKEN_LEN ; 
 scalar_t__ PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_LOG (char*,char const*,...) ; 
 int /*<<< orphan*/  RETRO_VFS_FILE_ACCESS_HINT_NONE ; 
 int /*<<< orphan*/  RETRO_VFS_FILE_ACCESS_READ ; 
 int errno ; 
 int /*<<< orphan*/  fill_pathname_basedir (char*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  fill_pathname_join (char*,char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ get_token (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  intfstream_close (char*) ; 
 int intfstream_get_file_size (char*) ; 
 scalar_t__ intfstream_init (TYPE_1__*) ; 
 int /*<<< orphan*/  intfstream_open (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (scalar_t__) ; 
 int sscanf (char*,char*,int*,int*,int*) ; 
 int /*<<< orphan*/  strerror (int) ; 
 scalar_t__ string_is_equal_noncase (char*,char*) ; 
 scalar_t__ update_cand (int*,int*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

int cue_find_track(const char *cue_path, bool first,
      uint64_t *offset, uint64_t *size, char *track_path, uint64_t max_len)
{
   int rv;
   intfstream_info_t info;
   char *tmp_token            = (char*)malloc(MAX_TOKEN_LEN);
   char *last_file            = (char*)malloc(PATH_MAX_LENGTH + 1);
   intfstream_t *fd           = NULL;
   int64_t last_index         = -1;
   int64_t cand_index         = -1;
   int32_t cand_track         = -1;
   int32_t track              = 0;
   uint64_t largest             = 0;
   int64_t volatile file_size = -1;
   bool is_data               = false;
   char *cue_dir              = (char*)malloc(PATH_MAX_LENGTH);
   cue_dir[0]                 = '\0';

   fill_pathname_basedir(cue_dir, cue_path, PATH_MAX_LENGTH);

   info.type        = INTFSTREAM_FILE;
   fd               = (intfstream_t*)intfstream_init(&info);

   if (!fd)
      goto error;

   if (!intfstream_open(fd, cue_path,
            RETRO_VFS_FILE_ACCESS_READ, RETRO_VFS_FILE_ACCESS_HINT_NONE))
   {
      RARCH_LOG("Could not open CUE file '%s': %s\n", cue_path,
            strerror(errno));
      goto error;
   }

   RARCH_LOG("Parsing CUE file '%s'...\n", cue_path);

   tmp_token[0] = '\0';

   rv = -EINVAL;

   while (get_token(fd, tmp_token, MAX_TOKEN_LEN) > 0)
   {
      if (string_is_equal_noncase(tmp_token, "FILE"))
      {
         /* Set last index to last EOF */
         if (file_size != -1)
            last_index = file_size;

         /* We're changing files since the candidate, update it */
         if (update_cand(&cand_index, &last_index, &largest, last_file, offset,
                         size, track_path, max_len))
         {
            rv = 0;
            if (first)
               goto clean;
         }

         get_token(fd, tmp_token, MAX_TOKEN_LEN);
         fill_pathname_join(last_file, cue_dir, tmp_token, PATH_MAX_LENGTH);

         file_size = intfstream_get_file_size(last_file);

         get_token(fd, tmp_token, MAX_TOKEN_LEN);

      }
      else if (string_is_equal_noncase(tmp_token, "TRACK"))
      {
         get_token(fd, tmp_token, MAX_TOKEN_LEN);
         get_token(fd, tmp_token, MAX_TOKEN_LEN);
         is_data = !string_is_equal_noncase(tmp_token, "AUDIO");
         ++track;
      }
      else if (string_is_equal_noncase(tmp_token, "INDEX"))
      {
         int m, s, f;
         get_token(fd, tmp_token, MAX_TOKEN_LEN);
         get_token(fd, tmp_token, MAX_TOKEN_LEN);

         if (sscanf(tmp_token, "%02d:%02d:%02d", &m, &s, &f) < 3)
         {
            RARCH_LOG("Error parsing time stamp '%s'\n", tmp_token);
            goto error;
         }

         last_index = (size_t) (((m * 60 + s) * 75) + f) * 2352;

         /* If we've changed tracks since the candidate, update it */
         if (cand_track != -1 && track != cand_track &&
             update_cand(&cand_index, &last_index, &largest, last_file, offset,
                         size, track_path, max_len))
         {
            rv = 0;
            if (first)
               goto clean;
         }

         if (!is_data)
            continue;

         if (cand_index == -1)
         {
            cand_index = last_index;
            cand_track = track;
         }
      }
   }

   if (file_size != -1)
      last_index = file_size;

   if (update_cand(&cand_index, &last_index, &largest, last_file, offset,
                   size, track_path, max_len))
      rv = 0;

clean:
   free(cue_dir);
   free(tmp_token);
   free(last_file);
   intfstream_close(fd);
   free(fd);
   return rv;

error:
   free(cue_dir);
   free(tmp_token);
   free(last_file);
   if (fd)
   {
      intfstream_close(fd);
      free(fd);
   }
   return -errno;
}