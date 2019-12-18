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
 int FALSE ; 
 scalar_t__ ISALNUM (char) ; 
 scalar_t__ STARTS_WITH_DRIVE_PREFIX (char const*) ; 
 scalar_t__ TOLOWER (char) ; 
 int TRUE ; 

bool Curl_is_absolute_url(const char *url, char *buf, size_t buflen)
{
  size_t i;
#ifdef WIN32
  if(STARTS_WITH_DRIVE_PREFIX(url))
    return FALSE;
#endif
  for(i = 0; i < buflen && url[i]; ++i) {
    char s = url[i];
    if((s == ':') && (url[i + 1] == '/')) {
      if(buf)
        buf[i] = 0;
      return TRUE;
    }
    /* RFC 3986 3.1 explains:
      scheme      = ALPHA *( ALPHA / DIGIT / "+" / "-" / "." )
    */
    else if(ISALNUM(s) || (s == '+') || (s == '-') || (s == '.') ) {
      if(buf)
        buf[i] = (char)TOLOWER(s);
    }
    else
      break;
  }
  return FALSE;
}