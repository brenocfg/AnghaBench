#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int level; int /*<<< orphan*/  charging; scalar_t__ dischargingTime; scalar_t__ chargingTime; } ;
typedef  TYPE_1__ EmscriptenBatteryEvent ;
typedef  int /*<<< orphan*/  EM_BOOL ;

/* Variables and functions */
 char* emscripten_event_type_to_string (int) ; 
 int /*<<< orphan*/  formatTime (char*,int) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char*,int,int /*<<< orphan*/ ) ; 

EM_BOOL battery_callback(int eventType, const EmscriptenBatteryEvent *e, void *userData)
{
  char t1[64];
  formatTime(t1, (int)e->chargingTime);
  char t2[64];
  formatTime(t2, (int)e->dischargingTime);
  printf("%s: chargingTime: %s, dischargingTime: %s, level: %g%%, charging: %d\n",
    emscripten_event_type_to_string(eventType), t1, t2, e->level*100, e->charging);

  return 0;
}