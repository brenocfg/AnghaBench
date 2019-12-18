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
typedef  int /*<<< orphan*/  tSkipListNode ;
struct TYPE_7__ {int /*<<< orphan*/  pRes; int /*<<< orphan*/  num; } ;
typedef  TYPE_1__ tQueryResultset ;
struct TYPE_9__ {char const* member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {int /*<<< orphan*/  pSkipList; } ;
typedef  TYPE_2__ STabObj ;
typedef  int /*<<< orphan*/  SPatternCompareInfo ;
typedef  TYPE_3__ SMeterNameFilterSupporter ;

/* Variables and functions */
 int /*<<< orphan*/  PATTERN_COMPARE_INFO_INITIALIZER ; 
 int /*<<< orphan*/  mgmtTablenameFilterCallback ; 
 int /*<<< orphan*/  tSkipListIterateList (int /*<<< orphan*/ ,int /*<<< orphan*/ ***,int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static void mgmtRetrieveFromLikeOptr(tQueryResultset* pRes, const char* str, STabObj* pMetric) {
  SPatternCompareInfo       info = PATTERN_COMPARE_INFO_INITIALIZER;
  SMeterNameFilterSupporter supporter = {info, str};

  pRes->num =
      tSkipListIterateList(pMetric->pSkipList, (tSkipListNode***)&pRes->pRes, mgmtTablenameFilterCallback, &supporter);
}