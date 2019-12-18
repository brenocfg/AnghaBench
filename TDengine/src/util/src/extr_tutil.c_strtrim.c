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
typedef  size_t int32_t ;

/* Variables and functions */

void strtrim(char *z) {
  int32_t i = 0;
  int32_t j = 0;

  int32_t delta = 0;
  while (z[j] == ' ') {
    ++j;
  }

  if (z[j] == 0) {
    z[0] = 0;
    return;
  }

  delta = j;

  int32_t stop = 0;
  while (z[j] != 0) {
    if (z[j] == ' ' && stop == 0) {
      stop = j;
    } else if (z[j] != ' ' && stop != 0) {
      stop = 0;
    }

    z[i++] = z[j++];
  }

  if (stop > 0) {
    z[stop - delta] = 0;
  } else if (j != i) {
    z[i] = 0;
  }
}