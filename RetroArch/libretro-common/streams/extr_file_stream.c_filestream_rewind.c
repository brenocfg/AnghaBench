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
struct TYPE_4__ {int error_flag; int eof_flag; } ;
typedef  TYPE_1__ RFILE ;

/* Variables and functions */
 int /*<<< orphan*/  RETRO_VFS_SEEK_POSITION_START ; 
 int /*<<< orphan*/  filestream_seek (TYPE_1__*,long,int /*<<< orphan*/ ) ; 

void filestream_rewind(RFILE *stream)
{
   if (!stream)
      return;
   filestream_seek(stream, 0L, RETRO_VFS_SEEK_POSITION_START);
   stream->error_flag = false;
   stream->eof_flag = false;
}