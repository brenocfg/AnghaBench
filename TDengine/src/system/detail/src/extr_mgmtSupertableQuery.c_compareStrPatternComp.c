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
typedef  scalar_t__ int32_t ;
struct TYPE_3__ {char member_0; char member_1; } ;
typedef  TYPE_1__ SPatternCompareInfo ;

/* Variables and functions */
 scalar_t__ TSDB_PATTERN_MATCH ; 
 scalar_t__ patternMatch (char const*,char const*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int32_t compareStrPatternComp(const void* pLeft, const void* pRight) {
  SPatternCompareInfo pInfo = {'%', '_'};

  const char* pattern = pRight;
  const char* str = pLeft;

  int32_t ret = patternMatch(pattern, str, strlen(str), &pInfo);

  return (ret == TSDB_PATTERN_MATCH) ? 0 : 1;
}