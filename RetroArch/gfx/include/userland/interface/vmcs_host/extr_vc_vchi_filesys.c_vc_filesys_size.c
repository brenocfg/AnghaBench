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

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  VC_O_RDONLY ; 
 int vc_filesys_close (int) ; 
 int vc_filesys_lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vc_filesys_open (char const*,int /*<<< orphan*/ ) ; 

int vc_filesys_size(const char *path)
{
   int fd;
   int end_pos = 0;
   int success = -1;
   if((fd = vc_filesys_open(path, VC_O_RDONLY)) == 0)
   {
      end_pos = vc_filesys_lseek(fd, 0, SEEK_END);
      success = vc_filesys_close(fd);
      (void)success;
   }

   return end_pos;
}