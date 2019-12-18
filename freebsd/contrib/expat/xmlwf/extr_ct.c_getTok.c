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

__attribute__((used)) static const char *
getTok(const char **pp)
{
  enum { inAtom, inString, init, inComment };
  int state = init;
  const char *tokStart = 0;
  for (;;) {
    switch (**pp) {
    case '\0':
      return 0;
    case ' ':
    case '\r':
    case '\t':
    case '\n':
      if (state == inAtom)
        return tokStart;
      break;
    case '(':
      if (state == inAtom)
        return tokStart;
      if (state != inString)
        state++;
      break;
    case ')':
      if (state > init)
        --state;
      else if (state != inString)
        return 0;
      break;
    case ';':
    case '/':
    case '=':
      if (state == inAtom)
        return tokStart;
      if (state == init)
        return (*pp)++;
      break;
    case '\\':
      ++*pp;
      if (**pp == '\0')
        return 0;
      break;
    case '"':
      switch (state) {
      case inString:
        ++*pp;
        return tokStart;
      case inAtom:
        return tokStart;
      case init:
        tokStart = *pp;
        state = inString;
        break;
      }
      break;
    default:
      if (state == init) {
        tokStart = *pp;
        state = inAtom;
      }
      break;
    }
    ++*pp;
  }
  /* not reached */
}