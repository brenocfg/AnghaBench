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
typedef  int /*<<< orphan*/  int8_t ;
struct TYPE_3__ {int /*<<< orphan*/  over; } ;
typedef  TYPE_1__ SQuery ;

/* Variables and functions */
 int /*<<< orphan*/  QUERY_NOT_COMPLETED ; 

void setQueryStatus(SQuery *pQuery, int8_t status) {
  if (status == QUERY_NOT_COMPLETED) {
    pQuery->over = status;
  } else {
    // QUERY_NOT_COMPLETED is not compatible with any other status, so clear its position first
    pQuery->over &= (~QUERY_NOT_COMPLETED);
    pQuery->over |= status;
  }
}