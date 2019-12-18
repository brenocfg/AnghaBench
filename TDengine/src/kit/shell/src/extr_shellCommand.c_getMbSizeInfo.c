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
 int /*<<< orphan*/  MAX_COMMAND_SIZE ; 
 scalar_t__ calloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbstowcs (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 int wcswidth (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void getMbSizeInfo(const char *str, int *size, int *width) {
  wchar_t *wc = (wchar_t *)calloc(sizeof(wchar_t), MAX_COMMAND_SIZE);
  *size = strlen(str);
  mbstowcs(wc, str, MAX_COMMAND_SIZE);
  *width = wcswidth(wc, MAX_COMMAND_SIZE);
  free(wc);
}