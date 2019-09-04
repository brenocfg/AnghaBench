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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EINTR ; 
 int errno ; 
 int fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  logmsg (char*,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int) ; 

void set_advisor_read_lock(const char *filename)
{
  FILE *lockfile;
  int error = 0;
  int res;

  do {
    lockfile = fopen(filename, "wb");
  } while((lockfile == NULL) && ((error = errno) == EINTR));
  if(lockfile == NULL) {
    logmsg("Error creating lock file %s error: %d %s",
           filename, error, strerror(error));
    return;
  }

  do {
    res = fclose(lockfile);
  } while(res && ((error = errno) == EINTR));
  if(res)
    logmsg("Error closing lock file %s error: %d %s",
           filename, error, strerror(error));
}