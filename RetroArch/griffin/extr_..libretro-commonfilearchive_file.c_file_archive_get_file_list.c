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
struct string_list {int dummy; } ;
struct TYPE_2__ {int found; scalar_t__ size; int /*<<< orphan*/ * needle; int /*<<< orphan*/ * opt_file; } ;
struct archive_extract_userdata {int found_file; int list_only; char* archive_name; struct string_list* list; TYPE_1__ decomp_state; int /*<<< orphan*/ * dec; scalar_t__ crc; int /*<<< orphan*/ * context; int /*<<< orphan*/ * ext; scalar_t__ archive_path_size; int /*<<< orphan*/ * extraction_directory; int /*<<< orphan*/ * extracted_file_path; int /*<<< orphan*/ * first_extracted_file_path; int /*<<< orphan*/  archive_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  file_archive_get_file_list_cb ; 
 int /*<<< orphan*/  file_archive_walk (char const*,char const*,int /*<<< orphan*/ ,struct archive_extract_userdata*) ; 
 int /*<<< orphan*/  string_list_free (struct string_list*) ; 
 struct string_list* string_list_new () ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

struct string_list *file_archive_get_file_list(const char *path,
      const char *valid_exts)
{
   struct archive_extract_userdata userdata;

   strlcpy(userdata.archive_path, path, sizeof(userdata.archive_path));
   userdata.first_extracted_file_path       = NULL;
   userdata.extracted_file_path             = NULL;
   userdata.extraction_directory            = NULL;
   userdata.archive_path_size               = 0;
   userdata.ext                             = NULL;
   userdata.list                            = string_list_new();
   userdata.found_file                      = false;
   userdata.list_only                       = true;
   userdata.context                         = NULL;
   userdata.archive_name[0]                 = '\0';
   userdata.crc                             = 0;
   userdata.dec                             = NULL;

   userdata.decomp_state.opt_file           = NULL;
   userdata.decomp_state.needle             = NULL;
   userdata.decomp_state.size               = 0;
   userdata.decomp_state.found              = false;

   if (!userdata.list)
      goto error;

   if (!file_archive_walk(path, valid_exts,
         file_archive_get_file_list_cb, &userdata))
      goto error;

   return userdata.list;

error:
   if (userdata.list)
      string_list_free(userdata.list);
   return NULL;
}