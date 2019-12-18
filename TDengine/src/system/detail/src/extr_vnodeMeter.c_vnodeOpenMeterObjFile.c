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
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int TSDB_FILENAME_LEN ; 
 int /*<<< orphan*/  dError (char*,char*,...) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int,...) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 char* tsDirectory ; 
 scalar_t__ vnodeCheckFileIntegrity (int /*<<< orphan*/ *) ; 

FILE *vnodeOpenMeterObjFile(int vnode) {
  FILE *      fp;
  char        fileName[TSDB_FILENAME_LEN];
  struct stat fstat;

  // check if directory exists
  sprintf(fileName, "%s/vnode%d", tsDirectory, vnode);
  if (stat(fileName, &fstat) < 0) return NULL;

  sprintf(fileName, "%s/vnode%d/meterObj.v%d", tsDirectory, vnode, vnode);
  if (stat(fileName, &fstat) < 0) return NULL;

  fp = fopen(fileName, "r+");
  if (fp != NULL) {
    if (vnodeCheckFileIntegrity(fp) < 0) {
      dError("file:%s is corrupted, need to restore it first", fileName);
      fclose(fp);

      // todo: how to recover
      exit(1);
    }
  } else {
    dError("failed to open %s, reason:%s", fileName, strerror(errno));
  }

  return fp;
}