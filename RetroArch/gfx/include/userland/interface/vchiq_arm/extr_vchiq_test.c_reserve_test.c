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
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  VC_CMA_IOC_RESERVE ; 
 int /*<<< orphan*/  close (int) ; 
 int ioctl (int,int /*<<< orphan*/ ,int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  sleep (int) ; 

__attribute__((used)) static void reserve_test(int reserve, int delay)
{
   int fd = open("/dev/vc-cma", O_RDWR);
   int rc = -1;
   if (fd >= 0)
   {
      rc = ioctl(fd, VC_CMA_IOC_RESERVE, reserve);
      if (rc == 0)
      {
         printf("Sleeping for %d seconds...\n", delay);
         sleep(delay);
      }
      else
         printf("* failed to ioctl /dev/vc-cma - rc %d\n", rc);
      close(fd);
   }
   else
      printf("* failed to open /dev/vc-cma - rc %d\n", fd);
}