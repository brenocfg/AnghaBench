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
 int MAXPATHLEN ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_WRONLY ; 
 int PERFINDEX_SUCCESS ; 
 int /*<<< orphan*/  VERIFY (int,char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int,long long) ; 
 int unlink (char*) ; 

int test_file_create(char* path, int thread_id, int num_threads, long long length) {
  long long i;
  int fd;
  int retval;
  char filepath[MAXPATHLEN];

  for(i=0; i<length; i++) {
    snprintf(filepath, MAXPATHLEN, "%s/file_create-%d-%lld", path, thread_id, i);
    fd = open(filepath, O_CREAT | O_EXCL | O_WRONLY, 0644);
    VERIFY(fd >= 0, "open failed");

    close(fd);
  }

  for(i=0; i<length; i++) {
    snprintf(filepath, MAXPATHLEN, "%s/file_create-%d-%lld", path, thread_id, i);
    retval = unlink(filepath);
    VERIFY(retval == 0, "unlink failed");
  }

  return PERFINDEX_SUCCESS;
}