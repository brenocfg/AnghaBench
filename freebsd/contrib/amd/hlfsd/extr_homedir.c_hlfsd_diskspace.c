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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  XLOG_ERROR ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ getpid () ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,char*,...) ; 
 int strlen (char*) ; 
 scalar_t__ unlink (char*) ; 
 int write (int,char*,int) ; 
 int /*<<< orphan*/  xsnprintf (char*,int,char*,char*,long) ; 

__attribute__((used)) static int
hlfsd_diskspace(char *path)
{
  char buf[MAXPATHLEN];
  int fd, len;

  xsnprintf(buf, sizeof(buf), "%s/._hlfstmp_%lu", path, (long) getpid());
  if ((fd = open(buf, O_RDWR | O_CREAT, 0600)) < 0) {
    plog(XLOG_ERROR, "cannot open %s: %m", buf);
    return -1;
  }
  len = strlen(buf);
  if (write(fd, buf, len) < len) {
    plog(XLOG_ERROR, "cannot write \"%s\" (%d bytes) to %s : %m", buf, len, buf);
    close(fd);
    unlink(buf);		/* cleanup just in case */
    return -1;
  }
  if (unlink(buf) < 0) {
    plog(XLOG_ERROR, "cannot unlink %s : %m", buf);
  }
  close(fd);
  return 0;
}