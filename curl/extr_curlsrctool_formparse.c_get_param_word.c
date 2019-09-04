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

__attribute__((used)) static char *get_param_word(char **str, char **end_pos, char endchar)
{
  char *ptr = *str;
  char *word_begin = NULL;
  char *ptr2;
  char *escape = NULL;

  /* the first non-space char is here */
  word_begin = ptr;
  if(*ptr == '"') {
    ++ptr;
    while(*ptr) {
      if(*ptr == '\\') {
        if(ptr[1] == '\\' || ptr[1] == '"') {
          /* remember the first escape position */
          if(!escape)
            escape = ptr;
          /* skip escape of back-slash or double-quote */
          ptr += 2;
          continue;
        }
      }
      if(*ptr == '"') {
        *end_pos = ptr;
        if(escape) {
          /* has escape, we restore the unescaped string here */
          ptr = ptr2 = escape;
          do {
            if(*ptr == '\\' && (ptr[1] == '\\' || ptr[1] == '"'))
              ++ptr;
            *ptr2++ = *ptr++;
          }
          while(ptr < *end_pos);
          *end_pos = ptr2;
        }
        while(*ptr && *ptr != ';' && *ptr != endchar)
          ++ptr;
        *str = ptr;
        return word_begin + 1;
      }
      ++ptr;
    }
    /* end quote is missing, treat it as non-quoted. */
    ptr = word_begin;
  }

  while(*ptr && *ptr != ';' && *ptr != endchar)
    ++ptr;
  *str = *end_pos = ptr;
  return word_begin;
}