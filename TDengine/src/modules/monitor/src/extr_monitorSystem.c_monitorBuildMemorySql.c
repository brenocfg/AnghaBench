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
struct TYPE_2__ {int /*<<< orphan*/  conn; } ;

/* Variables and functions */
 TYPE_1__* monitor ; 
 int /*<<< orphan*/  monitorError (char*,int /*<<< orphan*/ ) ; 
 int sprintf (char*,char*,float,float,int) ; 
 int taosGetProcMemory (float*) ; 
 int taosGetSysMemory (float*) ; 
 int tsTotalMemoryMB ; 

int monitorBuildMemorySql(char *sql) {
  float sysMemoryUsedMB = 0;
  bool  suc = taosGetSysMemory(&sysMemoryUsedMB);
  if (!suc) {
    monitorError("monitor:%p, get sys memory info failed.", monitor->conn);
  }

  float procMemoryUsedMB = 0;
  suc = taosGetProcMemory(&procMemoryUsedMB);
  if (!suc) {
    monitorError("monitor:%p, get proc memory info failed.", monitor->conn);
  }

  return sprintf(sql, ", %f, %f, %d", procMemoryUsedMB, sysMemoryUsedMB, tsTotalMemoryMB);
}