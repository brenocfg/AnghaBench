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
typedef  int /*<<< orphan*/  int64_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ TSDB_TIME_PRECISION_MICRO ; 
 int /*<<< orphan*/  taosGetTimestampMs () ; 
 int /*<<< orphan*/  taosGetTimestampUs () ; 

int64_t taosGetTimestamp(int32_t precision) {
  if (precision == TSDB_TIME_PRECISION_MICRO) {
    return taosGetTimestampUs();
  } else {
    return taosGetTimestampMs();
  }
}