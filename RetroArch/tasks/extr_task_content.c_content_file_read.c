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
typedef  int int64_t ;

/* Variables and functions */
 scalar_t__ file_archive_compressed_read (char const*,void**,int /*<<< orphan*/ *,int*) ; 
 int filestream_read_file (char const*,void**,int*) ; 
 scalar_t__ path_contains_compressed_file (char const*) ; 

__attribute__((used)) static int64_t content_file_read(const char *path, void **buf, int64_t *length)
{
#ifdef HAVE_COMPRESSION
   if (path_contains_compressed_file(path))
   {
      if (file_archive_compressed_read(path, buf, NULL, length))
         return 1;
   }
#endif
   return filestream_read_file(path, buf, length);
}