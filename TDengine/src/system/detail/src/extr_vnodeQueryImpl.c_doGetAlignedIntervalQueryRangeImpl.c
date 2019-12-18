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
typedef  scalar_t__ int64_t ;
struct TYPE_3__ {scalar_t__ nAggTimeInterval; int /*<<< orphan*/  precision; int /*<<< orphan*/  intervalTimeUnit; } ;
typedef  TYPE_1__ SQuery ;

/* Variables and functions */
 scalar_t__ INT64_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ taosGetIntervalStartTimestamp (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void doGetAlignedIntervalQueryRangeImpl(SQuery *pQuery, int64_t qualifiedKey, int64_t keyFirst, int64_t keyLast,
                                               int64_t *skey, int64_t *ekey) {
  assert(qualifiedKey >= keyFirst && qualifiedKey <= keyLast);

  if (keyFirst > (INT64_MAX - pQuery->nAggTimeInterval)) {
    /*
     * if the skey > INT64_MAX - pQuery->nAggTimeInterval, the query duration between
     * skey and ekey must be less than one interval.Therefore, no need to adjust the query ranges.
     */
    assert(keyLast - keyFirst < pQuery->nAggTimeInterval);

    *skey = keyFirst;
    *ekey = keyLast;
    return;
  }

  *skey = taosGetIntervalStartTimestamp(qualifiedKey, pQuery->nAggTimeInterval, pQuery->intervalTimeUnit,
                                        pQuery->precision);
  int64_t endKey = *skey + pQuery->nAggTimeInterval - 1;

  if (*skey < keyFirst) {
    *skey = keyFirst;
  }

  if (endKey < keyLast) {
    *ekey = endKey;
  } else {
    *ekey = keyLast;
  }
}