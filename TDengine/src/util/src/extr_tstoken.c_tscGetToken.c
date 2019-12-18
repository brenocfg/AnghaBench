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

/* Variables and functions */
 scalar_t__* delimiter ; 
 scalar_t__* operator ; 
 int /*<<< orphan*/  shiftStr (char*,char*) ; 

char *tscGetToken(char *string, char **token, int *tokenLen) {
  char quote = 0;

  while (*string != 0) {
    if (delimiter[*string]) {
      ++string;
    } else {
      break;
    }
  }

  char quotaChar = 0;
  if (*string == '\'' || *string == '\"') {
    quote = 1;
    quotaChar = *string;
    string++;
  }

  *token = string;
  /* not in string, return token */
  if (*string > 0 && operator[*string] && quote == 0) {
    string++;
    /* handle the case: insert into tabx using stable1 tags(-1)/tags(+1)
     * values(....) */
    if (operator[*string] &&(*string != '(' && *string != ')' && *string != '-' && *string != '+'))
      *tokenLen = 2;
    else
      *tokenLen = 1;
    return *token + *tokenLen;
  }

  while (*string != 0) {
    if (quote) {
      // handle escape situation: '\"', the " should not be eliminated
      if (*string == quotaChar) {
        if (*(string - 1) != '\\') {
          break;
        } else {
          shiftStr(string - 1, string);
        }
      } else {
        ++string;
      }
    } else {
      if (delimiter[*string]) break;

      if (operator[*string]) break;

      ++string;
    }
  }

  *tokenLen = (int)(string - *token);

  if (quotaChar != 0 && *string != 0 && *(string + 1) != 0) {
    return string + 1;
  } else {
    return string;
  }
}