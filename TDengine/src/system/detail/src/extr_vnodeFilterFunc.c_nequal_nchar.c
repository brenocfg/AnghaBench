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
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_4__ {int len; scalar_t__ pz; } ;
struct TYPE_5__ {int bytes; TYPE_1__ filterInfo; } ;
typedef  TYPE_2__ SColumnFilterElem ;

/* Variables and functions */
 int TSDB_NCHAR_SIZE ; 
 scalar_t__ wcsncmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

bool nequal_nchar(SColumnFilterElem *pFilter, char* minval, char *maxval) {
  if (pFilter->filterInfo.len > pFilter->bytes) {
    return true;
  }

  return wcsncmp((wchar_t *)pFilter->filterInfo.pz, (wchar_t*)minval, pFilter->bytes/TSDB_NCHAR_SIZE) != 0;
}