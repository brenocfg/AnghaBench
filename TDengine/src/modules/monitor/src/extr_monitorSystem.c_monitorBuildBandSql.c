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
 int sprintf (char*,char*,float) ; 
 int taosGetBandSpeed (float*) ; 

int monitorBuildBandSql(char *sql) {
  float bandSpeedKb = 0;
  bool  suc = taosGetBandSpeed(&bandSpeedKb);
  if (!suc) {
    monitorError("monitor:%p, get bandwidth speed failed.", monitor->conn);
  }

  return sprintf(sql, ", %f", bandSpeedKb);
}