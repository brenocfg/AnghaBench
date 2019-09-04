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
 int TRUE ; 
 scalar_t__ strcasecompare (char*,char const*) ; 
 char* strchr (char const*,char const) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncasecompare (char const*,char const*,size_t) ; 

__attribute__((used)) static bool check_noproxy(const char *name, const char *no_proxy)
{
  /* no_proxy=domain1.dom,host.domain2.dom
   *   (a comma-separated list of hosts which should
   *   not be proxied, or an asterisk to override
   *   all proxy variables)
   */
  if(no_proxy && no_proxy[0]) {
    size_t tok_start;
    size_t tok_end;
    const char *separator = ", ";
    size_t no_proxy_len;
    size_t namelen;
    char *endptr;
    if(strcasecompare("*", no_proxy)) {
      return TRUE;
    }

    /* NO_PROXY was specified and it wasn't just an asterisk */

    no_proxy_len = strlen(no_proxy);
    if(name[0] == '[') {
      /* IPv6 numerical address */
      endptr = strchr(name, ']');
      if(!endptr)
        return FALSE;
      name++;
      namelen = endptr - name;
    }
    else
      namelen = strlen(name);

    for(tok_start = 0; tok_start < no_proxy_len; tok_start = tok_end + 1) {
      while(tok_start < no_proxy_len &&
            strchr(separator, no_proxy[tok_start]) != NULL) {
        /* Look for the beginning of the token. */
        ++tok_start;
      }

      if(tok_start == no_proxy_len)
        break; /* It was all trailing separator chars, no more tokens. */

      for(tok_end = tok_start; tok_end < no_proxy_len &&
            strchr(separator, no_proxy[tok_end]) == NULL; ++tok_end)
        /* Look for the end of the token. */
        ;

      /* To match previous behaviour, where it was necessary to specify
       * ".local.com" to prevent matching "notlocal.com", we will leave
       * the '.' off.
       */
      if(no_proxy[tok_start] == '.')
        ++tok_start;

      if((tok_end - tok_start) <= namelen) {
        /* Match the last part of the name to the domain we are checking. */
        const char *checkn = name + namelen - (tok_end - tok_start);
        if(strncasecompare(no_proxy + tok_start, checkn,
                           tok_end - tok_start)) {
          if((tok_end - tok_start) == namelen || *(checkn - 1) == '.') {
            /* We either have an exact match, or the previous character is a .
             * so it is within the same domain, so no proxy for this host.
             */
            return TRUE;
          }
        }
      } /* if((tok_end - tok_start) <= namelen) */
    } /* for(tok_start = 0; tok_start < no_proxy_len;
         tok_start = tok_end + 1) */
  } /* NO_PROXY was specified and it wasn't just an asterisk */

  return FALSE;
}