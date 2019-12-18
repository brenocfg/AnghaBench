#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;
struct archive_extract_userdata {scalar_t__ crc; int /*<<< orphan*/  extracted_file_path; TYPE_1__ member_0; } ;
struct TYPE_6__ {scalar_t__ type; int /*<<< orphan*/ * backend; int /*<<< orphan*/ * data; int /*<<< orphan*/ * directory; int /*<<< orphan*/ * footer; int /*<<< orphan*/ * stream; int /*<<< orphan*/ * handle; scalar_t__ archive_size; } ;
typedef  TYPE_2__ file_archive_transfer_t ;

/* Variables and functions */
 scalar_t__ ARCHIVE_TRANSFER_INIT ; 
 scalar_t__ ARCHIVE_TRANSFER_ITERATE ; 
 int /*<<< orphan*/  file_archive_parse_file_iterate (TYPE_2__*,int*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct archive_extract_userdata*) ; 
 int /*<<< orphan*/  file_archive_parse_file_iterate_stop (TYPE_2__*) ; 
 int path_contains_compressed_file (char const*) ; 
 char* path_get_archive_delim (char const*) ; 
 scalar_t__ string_is_equal (int /*<<< orphan*/ ,char const*) ; 

uint32_t file_archive_get_file_crc32(const char *path)
{
   file_archive_transfer_t state;
   struct archive_extract_userdata userdata        = {{0}};
   bool returnerr                                  = false;
   const char *archive_path                        = NULL;
   bool contains_compressed = path_contains_compressed_file(path);

   if (contains_compressed)
   {
      archive_path = path_get_archive_delim(path);

      /* move pointer right after the delimiter to give us the path */
      if (archive_path)
         archive_path += 1;
   }

   state.type          = ARCHIVE_TRANSFER_INIT;
   state.archive_size  = 0;
   state.handle        = NULL;
   state.stream        = NULL;
   state.footer        = NULL;
   state.directory     = NULL;
   state.data          = NULL;
   state.backend       = NULL;

   /* Initialize and open archive first.
      Sets next state type to ITERATE. */
   file_archive_parse_file_iterate(&state,
            &returnerr, path, NULL, NULL,
            &userdata);

   for (;;)
   {
      /* Now find the first file in the archive. */
      if (state.type == ARCHIVE_TRANSFER_ITERATE)
         file_archive_parse_file_iterate(&state,
                  &returnerr, path, NULL, NULL,
                  &userdata);

      /* If no path specified within archive, stop after
       * finding the first file.
       */
      if (!contains_compressed)
         break;

      /* Stop when the right file in the archive is found. */
      if (archive_path)
      {
         if (string_is_equal(userdata.extracted_file_path, archive_path))
            break;
      }
      else
         break;
   }

   file_archive_parse_file_iterate_stop(&state);

   if (userdata.crc)
      return userdata.crc;

   return 0;
}