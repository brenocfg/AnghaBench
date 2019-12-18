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

/* Variables and functions */
 char* dataDir ; 
 int /*<<< orphan*/  dnodeCheckDbRunning (char*) ; 
 char* mgmtDirectory ; 
 int /*<<< orphan*/  mkdir (char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* tsDirectory ; 

int taosCreateTierDirectory() {
  struct stat dirstat;
  strcpy(tsDirectory, dataDir);
  if (stat(dataDir, &dirstat) < 0) {
    mkdir(dataDir, 0755);
  }

  char fileName[128];

  sprintf(fileName, "%s/tsdb", tsDirectory);
  mkdir(fileName, 0755);

  sprintf(fileName, "%s/data", tsDirectory);
  mkdir(fileName, 0755);

  sprintf(mgmtDirectory, "%s/mgmt", tsDirectory);
  sprintf(tsDirectory, "%s/tsdb", dataDir);
  dnodeCheckDbRunning(dataDir);

  return 0;
}