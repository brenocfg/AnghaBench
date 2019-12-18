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
struct TYPE_5__ {size_t nField; TYPE_1__* p; } ;
typedef  TYPE_2__ tFieldList ;
typedef  size_t int32_t ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_COL_NAME_LEN ; 
 scalar_t__ strncasecmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool has(tFieldList* pFieldList, int32_t startIdx, char* name) {
  for (int32_t j = startIdx; j < pFieldList->nField; ++j) {
    if (strncasecmp(name, pFieldList->p[j].name, TSDB_COL_NAME_LEN) == 0) return true;
  }

  return false;
}