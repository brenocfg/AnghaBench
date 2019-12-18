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
typedef  scalar_t__ int32_t ;

/* Variables and functions */

char *paGetToken(char *string, char **token, int32_t *tokenLen) {
  char quote = 0;

  while (*string != 0) {
    if (*string == ' ' || *string == '\t') {
      ++string;
    } else {
      break;
    }
  }

  if (*string == '@') {
    quote = 1;
    string++;
  }

  *token = string;

  while (*string != 0) {
    if (*string == '@' && quote) {
      //*string = 0;
      ++string;
      break;
    }

    if (*string == '#' || *string == '\n' || *string == '\r') {
      *string = 0;
      break;
    }

    if ((*string == ' ' || *string == '\t') && !quote) {
      break;
    } else {
      ++string;
    }
  }

  *tokenLen = (int32_t)(string - *token);
  if (quote) {
    *tokenLen = *tokenLen - 1;
  }

  return string;
}