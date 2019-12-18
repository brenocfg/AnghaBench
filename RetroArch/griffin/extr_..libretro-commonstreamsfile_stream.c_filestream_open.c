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
struct retro_vfs_file_handle {int dummy; } ;
struct TYPE_3__ {int error_flag; int eof_flag; struct retro_vfs_file_handle* hfile; } ;
typedef  TYPE_1__ RFILE ;

/* Variables and functions */
 scalar_t__ filestream_open_cb (char const*,unsigned int,unsigned int) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ retro_vfs_file_open_impl (char const*,unsigned int,unsigned int) ; 

RFILE* filestream_open(const char *path, unsigned mode, unsigned hints)
{
   struct retro_vfs_file_handle  *fp = NULL;
   RFILE* output                     = NULL;

   if (filestream_open_cb != NULL)
      fp = (struct retro_vfs_file_handle*)
         filestream_open_cb(path, mode, hints);
   else
      fp = (struct retro_vfs_file_handle*)
         retro_vfs_file_open_impl(path, mode, hints);

   if (!fp)
      return NULL;

   output             = (RFILE*)malloc(sizeof(RFILE));
   output->error_flag = false;
   output->eof_flag   = false;
   output->hfile      = fp;
   return output;
}