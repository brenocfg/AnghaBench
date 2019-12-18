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
typedef  enum rbmp_source_type { ____Placeholder_rbmp_source_type } rbmp_source_type ;
typedef  int /*<<< orphan*/  RFILE ;

/* Variables and functions */
 int RBMP_SOURCE_TYPE_ARGB8888 ; 
 int /*<<< orphan*/  RETRO_VFS_FILE_ACCESS_HINT_NONE ; 
 int /*<<< orphan*/  RETRO_VFS_FILE_ACCESS_WRITE ; 
 int /*<<< orphan*/  dump_content (int /*<<< orphan*/ *,void const*,unsigned int,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  filestream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * filestream_open (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int write_header_bmp (int /*<<< orphan*/ *,unsigned int,unsigned int,int) ; 

bool rbmp_save_image(
      const char *filename,
      const void *frame,
      unsigned width, unsigned height,
      unsigned pitch, enum rbmp_source_type type)
{
   bool ret    = false;
   RFILE *file = filestream_open(filename,
         RETRO_VFS_FILE_ACCESS_WRITE,
         RETRO_VFS_FILE_ACCESS_HINT_NONE);
   if (!file)
      return false;

   ret = write_header_bmp(file, width, height, type==RBMP_SOURCE_TYPE_ARGB8888);

   if (ret)
      dump_content(file, frame, width, height, pitch, type);

   filestream_close(file);

   return ret;
}