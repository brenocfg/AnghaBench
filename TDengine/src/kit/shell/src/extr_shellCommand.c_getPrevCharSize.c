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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  MB_CUR_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int countPrefixOnes (char const) ; 
 int mbtowc (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int wcwidth (int /*<<< orphan*/ ) ; 

void getPrevCharSize(const char *str, int pos, int *size, int *width) {
  assert(pos > 0);

  wchar_t wc;
  *size = 0;
  *width = 0;

  while (--pos >= 0) {
    *size += 1;

    if (str[pos] > 0 || countPrefixOnes(str[pos]) > 1) break;
  }

  int rc = mbtowc(&wc, str + pos, MB_CUR_MAX);
  assert(rc == *size);

  *width = wcwidth(wc);
}