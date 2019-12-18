#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ wchar_t ;
typedef  size_t int32_t ;
typedef  int /*<<< orphan*/  SPatternCompareInfo ;

/* Variables and functions */
 int TSDB_PATTERN_MATCH ; 
 size_t TSDB_PATTERN_NOMATCH ; 
 int TSDB_PATTERN_NOWILDCARDMATCH ; 
 scalar_t__ towlower (scalar_t__) ; 
 scalar_t__ towupper (scalar_t__) ; 
 size_t wcslen (scalar_t__ const*) ; 
 size_t wcsspn (scalar_t__ const*,scalar_t__*) ; 

int WCSPatternMatch(const wchar_t *patterStr, const wchar_t *str, size_t size, const SPatternCompareInfo *pInfo) {
  wchar_t c, c1;
  wchar_t matchOne = L'_';  // "_"
  wchar_t matchAll = L'%';  // "%"

  int32_t i = 0;
  int32_t j = 0;

  while ((c = patterStr[i++]) != 0) {
    if (c == matchAll) { /* Match "%" */

      while ((c = patterStr[i++]) == matchAll || c == matchOne) {
        if (c == matchOne && (j > size || str[j++] == 0)) {
          return TSDB_PATTERN_NOWILDCARDMATCH;
        }
      }
      if (c == 0) {
        return TSDB_PATTERN_MATCH;
      }

      wchar_t accept[3] = {towupper(c), towlower(c), 0};
      while (1) {
        size_t n = wcsspn(str, accept);

        str += n;
        if (str[0] == 0 || (n >= size - 1)) {
          break;
        }

        str++;

        int32_t ret = WCSPatternMatch(&patterStr[i], str, wcslen(str), pInfo);
        if (ret != TSDB_PATTERN_NOMATCH) {
          return ret;
        }
      }

      return TSDB_PATTERN_NOWILDCARDMATCH;
    }

    c1 = str[j++];

    if (j <= size) {
      if (c == c1 || towlower(c) == towlower(c1) || (c == matchOne && c1 != 0)) {
        continue;
      }
    }

    return TSDB_PATTERN_NOMATCH;
  }

  return (str[j] == 0 || j >= size) ? TSDB_PATTERN_MATCH : TSDB_PATTERN_NOMATCH;
}