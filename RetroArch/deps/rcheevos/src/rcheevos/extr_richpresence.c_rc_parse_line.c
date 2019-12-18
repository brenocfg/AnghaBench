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
 scalar_t__ isspace (char const) ; 

__attribute__((used)) static const char* rc_parse_line(const char* line, const char** end) {
  const char* nextline;
  const char* endline;

  /* get a single line */
  nextline = line;
  while (*nextline && *nextline != '\n')
    ++nextline;

  /* find a trailing comment marker (//) */
  endline = line;
  while (endline < nextline && (endline[0] != '/' || endline[1] != '/' || (endline > line && endline[-1] == '\\')))
    ++endline;

  /* remove trailing whitespace */
  if (endline == nextline) {
    if (endline > line && endline[-1] == '\r')
      --endline;
  } else {
    while (endline > line && isspace(endline[-1]))
      --endline;
  }

  /* end is pointing at the first character to ignore - makes subtraction for length easier */
  *end = endline;

  if (*nextline == '\n')
    ++nextline;
  return nextline;
}