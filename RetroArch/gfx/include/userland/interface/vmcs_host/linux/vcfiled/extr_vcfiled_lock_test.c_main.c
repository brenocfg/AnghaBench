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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  logmsg ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  sleep (int) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  usage (char const*) ; 
 scalar_t__ vcfiled_is_running (char const*) ; 
 int vcfiled_lock (char const*,int /*<<< orphan*/ ) ; 

int main(int argc, const char **argv)
{
   if (argc != 3)
   {
      usage(argv[0]);
   }
   const char *lockfile = argv[2];
   if (strcmp(argv[1], "lock") == 0)
   {
      int rc = vcfiled_lock(lockfile, logmsg);
      if (rc)
      {
         printf("failed to lock %s\n", lockfile);
         exit(1);
      }
      sleep(300);
   }
   else if (strcmp(argv[1], "check") == 0)
   {
      printf("%s\n",
             vcfiled_is_running(lockfile) ?
             "running" : "not running");
   }
   else
   {
      usage(argv[0]);
   }
   return 0;
}