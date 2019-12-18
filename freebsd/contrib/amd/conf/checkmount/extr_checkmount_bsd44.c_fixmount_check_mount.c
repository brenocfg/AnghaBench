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
struct statfs {int /*<<< orphan*/  f_mntfromname; } ;
struct in_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MNT_NOWAIT ; 
 scalar_t__ STREQ (char*,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int getmntinfo (struct statfs**,int /*<<< orphan*/ ) ; 
 scalar_t__ is_same_host (int /*<<< orphan*/ ,char*,struct in_addr) ; 
 int /*<<< orphan*/  perror (char*) ; 
 char* strchr (int /*<<< orphan*/ ,char) ; 

int
fixmount_check_mount(char *host, struct in_addr hostaddr, char *path)
{
  struct statfs *mntbufp, *mntp;
  int nloc, i;
  char *colon;

  /* read mount table from kernel */
  nloc = getmntinfo(&mntbufp, MNT_NOWAIT);
  if (nloc <= 0) {
    perror("getmntinfo");
    exit(1);
  }

  mntp = mntbufp;
  for (i=0; i<nloc; ++i) {
    if ((colon = strchr(mntp->f_mntfromname, ':'))) {
      *colon = '\0';
      if (STREQ(colon + 1, path) &&
	  is_same_host(mntp->f_mntfromname, host, hostaddr))
	return 1;
    }
  }

  return 0;
}