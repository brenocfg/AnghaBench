#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_4__ {int numOfFilters; int /*<<< orphan*/ * filterInfo; } ;
typedef  int /*<<< orphan*/  SColumnFilterInfo ;
typedef  TYPE_1__ SColumnBase ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  tscColumnFilterInfoCopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void tscColumnBaseCopy(SColumnBase* dst, const SColumnBase* src) {
  assert (src != NULL && dst != NULL);

  *dst = *src;

  if (src->numOfFilters > 0) {
    dst->filterInfo = calloc(1, src->numOfFilters * sizeof(SColumnFilterInfo));

    for (int32_t j = 0; j < src->numOfFilters; ++j) {
      tscColumnFilterInfoCopy(&dst->filterInfo[j], &src->filterInfo[j]);
    }
  } else {
    assert(src->filterInfo == NULL);
  }
}