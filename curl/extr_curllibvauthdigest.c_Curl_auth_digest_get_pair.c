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
 int DIGEST_MAX_CONTENT_LENGTH ; 
 int DIGEST_MAX_VALUE_LENGTH ; 
 int FALSE ; 
 int TRUE ; 

bool Curl_auth_digest_get_pair(const char *str, char *value, char *content,
                               const char **endptr)
{
  int c;
  bool starts_with_quote = FALSE;
  bool escape = FALSE;

  for(c = DIGEST_MAX_VALUE_LENGTH - 1; (*str && (*str != '=') && c--);)
    *value++ = *str++;
  *value = 0;

  if('=' != *str++)
    /* eek, no match */
    return FALSE;

  if('\"' == *str) {
    /* This starts with a quote so it must end with one as well! */
    str++;
    starts_with_quote = TRUE;
  }

  for(c = DIGEST_MAX_CONTENT_LENGTH - 1; *str && c--; str++) {
    switch(*str) {
    case '\\':
      if(!escape) {
        /* possibly the start of an escaped quote */
        escape = TRUE;
        *content++ = '\\'; /* Even though this is an escape character, we still
                              store it as-is in the target buffer */
        continue;
      }
      break;

    case ',':
      if(!starts_with_quote) {
        /* This signals the end of the content if we didn't get a starting
           quote and then we do "sloppy" parsing */
        c = 0; /* the end */
        continue;
      }
      break;

    case '\r':
    case '\n':
      /* end of string */
      c = 0;
      continue;

    case '\"':
      if(!escape && starts_with_quote) {
        /* end of string */
        c = 0;
        continue;
      }
      break;
    }

    escape = FALSE;
    *content++ = *str;
  }

  *content = 0;
  *endptr = str;

  return TRUE;
}