#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_4__ {scalar_t__ size; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ file_archive_file_data_t ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  file_archive_free (TYPE_1__*) ; 
 int filestream_read_file (char const*,int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static file_archive_file_data_t* file_archive_open(const char *path)
{
   int64_t ret            = -1;
   bool read_from_file    = false;
   file_archive_file_data_t *data = (file_archive_file_data_t*)
      calloc(1, sizeof(*data));

   if (!data)
      return NULL;

   read_from_file = filestream_read_file(path, &data->data, &ret);

   /* Failed to open archive? */
   if (!read_from_file || ret < 0)
      goto error;

   data->size = ret;
   return data;

error:
   file_archive_free(data);
   return NULL;
}