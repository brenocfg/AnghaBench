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
typedef  int /*<<< orphan*/  int8_t ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  TSKEY ;

/* Variables and functions */
 scalar_t__ TSQL_SO_ASC ; 
 int /*<<< orphan*/  taosGetIntervalStartTimestamp (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

TSKEY taosGetRevisedEndKey(TSKEY ekey, int32_t order, int32_t timeInterval, int8_t intervalTimeUnit, int8_t precision) {
  if (order == TSQL_SO_ASC) {
    return ekey;
  } else {
    return taosGetIntervalStartTimestamp(ekey, timeInterval, intervalTimeUnit, precision);
  }
}