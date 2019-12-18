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
struct TYPE_2__ {int /*<<< orphan*/  initTimer; } ;

/* Variables and functions */
 TYPE_1__* monitor ; 
 int /*<<< orphan*/  monitorInitConn ; 
 int /*<<< orphan*/  monitorInitSystem () ; 
 int /*<<< orphan*/  taosTmrReset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tscTmr ; 

int monitorStartSystem() {
  if (monitor == NULL) {
    monitorInitSystem();
  }
  taosTmrReset(monitorInitConn, 10, NULL, tscTmr, &monitor->initTimer);
  return 0;
}