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
struct stub_state {scalar_t__* stack; scalar_t__ i; } ;
typedef  int /*<<< orphan*/  RFILE ;

/* Variables and functions */
 int /*<<< orphan*/  RETRO_VFS_FILE_ACCESS_HINT_NONE ; 
 int /*<<< orphan*/  RETRO_VFS_FILE_ACCESS_READ ; 
 int /*<<< orphan*/  filestream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * filestream_open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  rmsgpack_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct stub_state*) ; 
 int /*<<< orphan*/  stub_callbacks ; 

int main(void)
{
   struct stub_state state;
   RFILE *fd = filestream_open("test.msgpack",
         RETRO_VFS_FILE_ACCESS_READ,
         RETRO_VFS_FILE_ACCESS_HINT_NONE);

   state.i        = 0;
   state.stack[0] = 0;

   rmsgpack_read(fd, &stub_callbacks, &state);

   printf("Test succeeded.\n");
   filestream_close(fd);

   return 0;
}