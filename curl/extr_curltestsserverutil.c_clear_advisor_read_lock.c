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
 int EINTR ; 
 int errno ; 
 int /*<<< orphan*/  logmsg (char*,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int unlink (char const*) ; 

void clear_advisor_read_lock(const char *filename)
{
  int error = 0;
  int res;

  /*
  ** Log all removal failures. Even those due to file not existing.
  ** This allows to detect if unexpectedly the file has already been
  ** removed by a process different than the one that should do this.
  */

  do {
    res = unlink(filename);
  } while(res && ((error = errno) == EINTR));
  if(res)
    logmsg("Error removing lock file %s error: %d %s",
           filename, error, strerror(error));
}