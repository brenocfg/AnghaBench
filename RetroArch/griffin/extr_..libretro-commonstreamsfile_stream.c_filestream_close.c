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
struct retro_vfs_file_handle {int dummy; } ;
typedef  int /*<<< orphan*/  libretro_vfs_implementation_file ;
struct TYPE_4__ {struct retro_vfs_file_handle* hfile; } ;
typedef  TYPE_1__ RFILE ;

/* Variables and functions */
 int filestream_close_cb (struct retro_vfs_file_handle*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int retro_vfs_file_close_impl (int /*<<< orphan*/ *) ; 

int filestream_close(RFILE *stream)
{
   int output;
   struct retro_vfs_file_handle* fp = stream->hfile;

   if (filestream_close_cb != NULL)
      output = filestream_close_cb(fp);
   else
      output = retro_vfs_file_close_impl((libretro_vfs_implementation_file*)fp);

   if (output == 0)
      free(stream);

   return output;
}