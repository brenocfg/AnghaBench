#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int maxSessions; } ;
struct TYPE_4__ {TYPE_1__ cfg; } ;
typedef  int /*<<< orphan*/  TSCKSUM ;
typedef  int /*<<< orphan*/  SCompHeader ;

/* Variables and functions */
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int S_IRWXG ; 
 int S_IRWXO ; 
 int S_IRWXU ; 
 int TSDB_FILENAME_LEN ; 
 int /*<<< orphan*/  TSDB_FILE_HEADER_LEN ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dError (char*,...) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosCalcChecksumAppend (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  twrite (int,char*,int) ; 
 int /*<<< orphan*/  vnodeCreateFileHeaderFd (int) ; 
 scalar_t__ vnodeCreateHeadDataFile (int,int,char*,char*,char*) ; 
 TYPE_2__* vnodeList ; 

int vnodeCreateEmptyCompFile(int vnode, int fileId) {
  char  headName[TSDB_FILENAME_LEN];
  char  dataName[TSDB_FILENAME_LEN];
  char  lastName[TSDB_FILENAME_LEN];
  int   tfd;
  char *temp;

  if (vnodeCreateHeadDataFile(vnode, fileId, headName, dataName, lastName) < 0) {
    dError("failed to create head data file, vnode: %d, fileId: %d", vnode, fileId);
    return -1;
  }

  tfd = open(headName, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
  if (tfd < 0) {
    dError("failed to create head file:%s, reason:%s", headName, strerror(errno));
    return -1;
  }

  vnodeCreateFileHeaderFd(tfd);
  int size = sizeof(SCompHeader) * vnodeList[vnode].cfg.maxSessions + sizeof(TSCKSUM);
  temp = malloc(size);
  memset(temp, 0, size);
  taosCalcChecksumAppend(0, (uint8_t *)temp, size);

  lseek(tfd, TSDB_FILE_HEADER_LEN, SEEK_SET);
  twrite(tfd, temp, size);
  free(temp);
  close(tfd);

  tfd = open(dataName, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
  if (tfd < 0) {
    dError("failed to create data file:%s, reason:%s", dataName, strerror(errno));
    return -1;
  }
  vnodeCreateFileHeaderFd(tfd);
  close(tfd);

  tfd = open(lastName, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
  if (tfd < 0) {
    dError("failed to create last file:%s, reason:%s", lastName, strerror(errno));
    return -1;
  }
  vnodeCreateFileHeaderFd(tfd);
  close(tfd);

  return 0;
}