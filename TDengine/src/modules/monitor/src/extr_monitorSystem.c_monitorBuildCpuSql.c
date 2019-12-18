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
 int taosGetCpuUsage (float*,float*) ; 
 int tsNumOfCores ; 

int monitorBuildCpuSql(char *sql) {
  float sysCpuUsage = 0, procCpuUsage = 0;
  bool  suc = taosGetCpuUsage(&sysCpuUsage, &procCpuUsage);
  if (!suc) {
    monitorError("monitor:%p, get cpu usage failed.", monitor->conn);
  }

  if (sysCpuUsage <= procCpuUsage) {
    sysCpuUsage = procCpuUsage + (float)0.1;
  }

  return sprintf(sql, ", %f, %f, %d", procCpuUsage, sysCpuUsage, tsNumOfCores);
}