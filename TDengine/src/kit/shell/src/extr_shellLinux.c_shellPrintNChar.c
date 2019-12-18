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
 int mbtowc (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int wcwidth (int /*<<< orphan*/ ) ; 

void shellPrintNChar(char *str, int width, bool printMode) {
  int col_left = width;
  wchar_t wc;
  while (col_left > 0) {
    if (*str == '\0') break;
    char *tstr = str;
    int byte_width = mbtowc(&wc, tstr, MB_CUR_MAX);
    if (byte_width <= 0) break;
    int col_width = wcwidth(wc);
    if (col_width <= 0) {
      str += byte_width;
      continue;
    }
    if (col_left < col_width) break;
    printf("%lc", wc);
    str += byte_width;
    col_left -= col_width;
  }

  while (col_left > 0) {
    printf(" ");
    col_left--;
  }

  if (!printMode) {
    printf("|");
  } else {
    printf("\n");
  }
}