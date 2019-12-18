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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {int /*<<< orphan*/  cond; int /*<<< orphan*/  uid; } ;
struct TYPE_4__ {size_t numOfTagCond; TYPE_2__* cond; } ;
typedef  TYPE_1__ STagCond ;
typedef  TYPE_2__ SCond ;

/* Variables and functions */
 int /*<<< orphan*/  SStringCreate (char const*) ; 
 size_t strlen (char const*) ; 

void tsSetMetricQueryCond(STagCond* pTagCond, uint64_t uid, const char* str) {
  size_t len = strlen(str);
  if (len == 0) {
    return;
  }

  SCond* pDest = &pTagCond->cond[pTagCond->numOfTagCond];
  pDest->uid = uid;
  pDest->cond = SStringCreate(str);

  pTagCond->numOfTagCond += 1;
}