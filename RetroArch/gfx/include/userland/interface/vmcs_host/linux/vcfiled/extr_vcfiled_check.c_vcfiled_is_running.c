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
struct flock {int l_len; scalar_t__ l_pid; scalar_t__ l_start; int /*<<< orphan*/  l_whence; int /*<<< orphan*/  l_type; } ;
typedef  int /*<<< orphan*/  flock ;

/* Variables and functions */
 int /*<<< orphan*/  F_GETLK ; 
 int /*<<< orphan*/  F_WRLCK ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  errno ; 
 int fcntl (int,int /*<<< orphan*/ ,struct flock*) ; 
 int /*<<< orphan*/  memset (struct flock*,int /*<<< orphan*/ ,int) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,char const*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

int vcfiled_is_running(const char *filename)
{
   int ret;

   int fd = open(filename, O_RDONLY);
   if (fd < 0)
   {
      // file not there, so filed not running
      ret = 0;
   }

   else
   {
      struct flock flock;
      memset(&flock, 0, sizeof(flock));
      flock.l_type   = F_WRLCK;
      flock.l_whence = SEEK_SET;
      flock.l_start  = 0;
      flock.l_len    = 1;
      int rc = fcntl(fd, F_GETLK, &flock);
      if (rc != 0)
      {
         /* could not access lock info */
         printf("%s: Could not access lockfile %s: %s\n",
            "vmcs_main", filename, strerror(errno));
         ret = 0;
      }
      else if (flock.l_pid == 0)
      {
         /* file is unlocked, so filed not running */
         ret = 0;
      }
      else
      {
         /* file is locked, so filed is running */
         ret = 1;
      }
   }
   /* coverity[leaked_handle] - fd left open on purpose */
   return ret;
}