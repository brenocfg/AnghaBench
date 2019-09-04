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

__attribute__((used)) static const char *unslashquote(const char *line, char *param)
{
  while(*line && (*line != '\"')) {
    if(*line == '\\') {
      char out;
      line++;

      /* default is to output the letter after the backslash */
      switch(out = *line) {
      case '\0':
        continue; /* this'll break out of the loop */
      case 't':
        out = '\t';
        break;
      case 'n':
        out = '\n';
        break;
      case 'r':
        out = '\r';
        break;
      case 'v':
        out = '\v';
        break;
      }
      *param++ = out;
      line++;
    }
    else
      *param++ = *line++;
  }
  *param = '\0'; /* always zero terminate */
  return line;
}