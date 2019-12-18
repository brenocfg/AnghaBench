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
struct string_list {int size; TYPE_1__* elems; } ;
struct file_archive_file_backend {int (* compressed_file_read ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,char const*) ;} ;
typedef  int int64_t ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 struct string_list* file_archive_filename_split (char const*) ; 
 struct file_archive_file_backend* file_archive_get_file_backend (int /*<<< orphan*/ ) ; 
 scalar_t__ path_is_valid (char const*) ; 
 int /*<<< orphan*/  string_list_free (struct string_list*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,char const*) ; 

int file_archive_compressed_read(
      const char * path, void **buf,
      const char* optional_filename, int64_t *length)
{
   const struct 
      file_archive_file_backend *backend = NULL;
   struct string_list *str_list          = NULL;

   /* Safety check.
    * If optional_filename and optional_filename
    * exists, we simply return 0,
    * hoping that optional_filename is the
    * same as requested.
    */
   if (optional_filename && path_is_valid(optional_filename))
   {
      *length = 0;
      return 1;
   }

   str_list       = file_archive_filename_split(path);
   /* We assure that there is something after the '#' symbol.
    *
    * This error condition happens for example, when
    * path = /path/to/file.7z, or
    * path = /path/to/file.7z#
    */
   if (str_list->size <= 1)
   {
      /* could not extract string and substring. */
      string_list_free(str_list);
      *length = 0;
      return 0;
   }

   backend = file_archive_get_file_backend(str_list->elems[0].data);
   *length = backend->compressed_file_read(str_list->elems[0].data,
         str_list->elems[1].data, buf, optional_filename);

   string_list_free(str_list);

   if (*length != -1)
      return 1;

   return 0;
}