#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ pz; } ;
struct TYPE_5__ {int /*<<< orphan*/  bytes; TYPE_1__ filterInfo; } ;
typedef  int /*<<< orphan*/  SPatternCompareInfo ;
typedef  TYPE_2__ SColumnFilterElem ;

/* Variables and functions */
 int /*<<< orphan*/  PATTERN_COMPARE_INFO_INITIALIZER ; 
 scalar_t__ TSDB_PATTERN_MATCH ; 
 scalar_t__ patternMatch (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool like_str(SColumnFilterElem *pFilter, char *minval, char *maxval) {
  SPatternCompareInfo info = PATTERN_COMPARE_INFO_INITIALIZER;

  return patternMatch((char *)pFilter->filterInfo.pz, minval, pFilter->bytes, &info) == TSDB_PATTERN_MATCH;
}