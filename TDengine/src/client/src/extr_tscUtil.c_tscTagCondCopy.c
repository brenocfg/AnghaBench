#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_7__ {int /*<<< orphan*/  uid; int /*<<< orphan*/  cond; } ;
struct TYPE_9__ {size_t numOfTagCond; int /*<<< orphan*/  relType; TYPE_2__* cond; int /*<<< orphan*/  joinInfo; TYPE_1__ tbnameCond; } ;
struct TYPE_8__ {int /*<<< orphan*/  uid; int /*<<< orphan*/  cond; } ;
typedef  TYPE_3__ STagCond ;
typedef  int /*<<< orphan*/  SJoinInfo ;

/* Variables and functions */
 int /*<<< orphan*/  SStringCopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

void tscTagCondCopy(STagCond* dest, const STagCond* src) {
  memset(dest, 0, sizeof(STagCond));

  SStringCopy(&dest->tbnameCond.cond, &src->tbnameCond.cond);
  dest->tbnameCond.uid = src->tbnameCond.uid;

  memcpy(&dest->joinInfo, &src->joinInfo, sizeof(SJoinInfo));

  for (int32_t i = 0; i < src->numOfTagCond; ++i) {
    SStringCopy(&dest->cond[i].cond, &src->cond[i].cond);
    dest->cond[i].uid = src->cond[i].uid;
  }

  dest->relType = src->relType;
  dest->numOfTagCond = src->numOfTagCond;
}