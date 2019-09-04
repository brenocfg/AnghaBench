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
typedef  int /*<<< orphan*/  CURLUcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLUE_MALFORMED_INPUT ; 
 int /*<<< orphan*/  CURLUE_OK ; 
 size_t strcspn (char*,char*) ; 
 size_t strlen (char*) ; 
 size_t strspn (char*,char const*) ; 

__attribute__((used)) static CURLUcode hostname_check(char *hostname, unsigned int flags)
{
  const char *l = NULL; /* accepted characters */
  size_t len;
  size_t hlen = strlen(hostname);
  (void)flags;

  if(hostname[0] == '[') {
    hostname++;
    l = "0123456789abcdefABCDEF::.%";
    hlen -= 2;
  }

  if(l) {
    /* only valid letters are ok */
    len = strspn(hostname, l);
    if(hlen != len)
      /* hostname with bad content */
      return CURLUE_MALFORMED_INPUT;
  }
  else {
    /* letters from the second string is not ok */
    len = strcspn(hostname, " ");
    if(hlen != len)
      /* hostname with bad content */
      return CURLUE_MALFORMED_INPUT;
  }
  return CURLUE_OK;
}