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
 size_t CURL_ZERO_TERMINATED ; 
 int /*<<< orphan*/  isprint (unsigned char) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  msnprintf (char*,int,char*,unsigned int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static char *c_escape(const char *str, size_t len)
{
  const char *s;
  unsigned char c;
  char *escaped, *e;

  if(len == CURL_ZERO_TERMINATED)
    len = strlen(str);

  /* Check for possible overflow. */
  if(len > (~(size_t) 0) / 4)
    return NULL;

  /* Allocate space based on worst-case */
  escaped = malloc(4 * len + 1);
  if(!escaped)
    return NULL;

  e = escaped;
  for(s = str; (c = *s) != '\0'; s++) {
    if(c == '\n') {
      strcpy(e, "\\n");
      e += 2;
    }
    else if(c == '\r') {
      strcpy(e, "\\r");
      e += 2;
    }
    else if(c == '\t') {
      strcpy(e, "\\t");
      e += 2;
    }
    else if(c == '\\') {
      strcpy(e, "\\\\");
      e += 2;
    }
    else if(c == '"') {
      strcpy(e, "\\\"");
      e += 2;
    }
    else if(! isprint(c)) {
      msnprintf(e, 5, "\\%03o", (unsigned)c);
      e += 4;
    }
    else
      *e++ = c;
  }
  *e = '\0';
  return escaped;
}