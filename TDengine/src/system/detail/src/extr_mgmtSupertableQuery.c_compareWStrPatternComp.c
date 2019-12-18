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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_3__ {char member_0; char member_1; } ;
typedef  TYPE_1__ SPatternCompareInfo ;

/* Variables and functions */
 scalar_t__ TSDB_PATTERN_MATCH ; 
 scalar_t__ WCSPatternMatch (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  wcslen (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int32_t compareWStrPatternComp(const void* pLeft, const void* pRight) {
  SPatternCompareInfo pInfo = {'%', '_'};

  const wchar_t* pattern = pRight;
  const wchar_t* str = pLeft;

  int32_t ret = WCSPatternMatch(pattern, str, wcslen(str), &pInfo);

  return (ret == TSDB_PATTERN_MATCH) ? 0 : 1;
}