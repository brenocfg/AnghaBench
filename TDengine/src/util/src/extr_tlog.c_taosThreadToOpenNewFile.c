#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int fd; } ;

/* Variables and functions */
 int LOG_FILE_NAME_LEN ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int S_IRWXG ; 
 int S_IRWXO ; 
 int S_IRWXU ; 
 TYPE_1__* logHandle ; 
 int /*<<< orphan*/  lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open (char*,int,int) ; 
 scalar_t__ openInProgress ; 
 int /*<<< orphan*/  pPrint (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int) ; 
 int /*<<< orphan*/  taosCloseLogByFd (int) ; 
 int /*<<< orphan*/  taosLockFile (int) ; 
 int taosLogFlag ; 
 scalar_t__ taosLogLines ; 
 char* taosLogName ; 
 int /*<<< orphan*/  umask (int /*<<< orphan*/ ) ; 

void *taosThreadToOpenNewFile(void *param) {
  char name[LOG_FILE_NAME_LEN];

  taosLogFlag ^= 1;
  taosLogLines = 0;
  sprintf(name, "%s.%d", taosLogName, taosLogFlag);

  umask(0);

  int fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
  taosLockFile(fd);
  lseek(fd, 0, SEEK_SET);

  int oldFd = logHandle->fd;
  logHandle->fd = fd;
  taosLogLines = 0;
  openInProgress = 0;
  pPrint("new log file is opened!!!");

  taosCloseLogByFd(oldFd);
  return NULL;
}