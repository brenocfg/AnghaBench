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
struct utsname {int /*<<< orphan*/  machine; int /*<<< orphan*/  version; int /*<<< orphan*/  release; int /*<<< orphan*/  nodename; int /*<<< orphan*/  sysname; } ;

/* Variables and functions */
 int /*<<< orphan*/  pPrint (char*,...) ; 
 int /*<<< orphan*/  tsNumOfCores ; 
 int /*<<< orphan*/  tsOpenMax ; 
 int /*<<< orphan*/  tsPageSize ; 
 int /*<<< orphan*/  tsStreamMax ; 
 int /*<<< orphan*/  tsTotalDataDirGB ; 
 int /*<<< orphan*/  tsTotalMemoryMB ; 
 scalar_t__ uname (struct utsname*) ; 

void tsPrintOsInfo() {
  pPrint(" os pageSize:            %ld(KB)", tsPageSize);
  pPrint(" os openMax:             %ld", tsOpenMax);
  pPrint(" os streamMax:           %ld", tsStreamMax);
  pPrint(" os numOfCores:          %d", tsNumOfCores);
  pPrint(" os totalDisk:           %f(GB)", tsTotalDataDirGB);
  pPrint(" os totalMemory:         %d(MB)", tsTotalMemoryMB);

  struct utsname buf;
  if (uname(&buf)) {
    pPrint(" can't fetch os info");
    return;
  }
  pPrint(" os sysname:             %s", buf.sysname);
  pPrint(" os nodename:            %s", buf.nodename);
  pPrint(" os release:             %s", buf.release);
  pPrint(" os version:             %s", buf.version);
  pPrint(" os machine:             %s", buf.machine);
}