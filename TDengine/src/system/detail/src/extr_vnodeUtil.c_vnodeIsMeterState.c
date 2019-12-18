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
typedef  int int32_t ;
struct TYPE_3__ {int state; } ;
typedef  TYPE_1__ SMeterObj ;

/* Variables and functions */
 int TSDB_METER_STATE_DELETING ; 
 int TSDB_METER_STATE_READY ; 

bool vnodeIsMeterState(SMeterObj* pMeterObj, int32_t state) {
  if (state == TSDB_METER_STATE_READY) {
    return pMeterObj->state == TSDB_METER_STATE_READY;
  } else if (state == TSDB_METER_STATE_DELETING) {
    return pMeterObj->state >= state;
  } else {
    return (((pMeterObj->state) & state) == state);
  }
}