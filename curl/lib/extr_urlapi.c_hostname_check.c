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
struct Curl_URL {int /*<<< orphan*/  zoneid; } ;
typedef  int /*<<< orphan*/  CURLUcode ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  CURLUE_MALFORMED_INPUT ; 
 int /*<<< orphan*/  CURLUE_NO_HOST ; 
 int /*<<< orphan*/  CURLUE_OK ; 
 int /*<<< orphan*/  CURLUE_OUT_OF_MEMORY ; 
 int Curl_inet_pton (int /*<<< orphan*/ ,char*,char*) ; 
 size_t strcspn (char*,char*) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 size_t strspn (char*,char const*) ; 

__attribute__((used)) static CURLUcode hostname_check(struct Curl_URL *u, char *hostname)
{
  size_t len;
  size_t hlen = strlen(hostname);

  if(hostname[0] == '[') {
#ifdef ENABLE_IPV6
    char dest[16]; /* fits a binary IPv6 address */
#endif
    const char *l = "0123456789abcdefABCDEF:.";
    if(hlen < 5) /* '[::1]' is the shortest possible valid string */
      return CURLUE_MALFORMED_INPUT;
    hostname++;
    hlen -= 2;

    if(hostname[hlen] != ']')
      return CURLUE_MALFORMED_INPUT;

    /* only valid letters are ok */
    len = strspn(hostname, l);
    if(hlen != len) {
      hlen = len;
      if(hostname[len] == '%') {
        /* this could now be '%[zone id]' */
        char zoneid[16];
        int i = 0;
        char *h = &hostname[len + 1];
        /* pass '25' if present and is a url encoded percent sign */
        if(!strncmp(h, "25", 2) && h[2] && (h[2] != ']'))
          h += 2;
        while(*h && (*h != ']') && (i < 15))
          zoneid[i++] = *h++;
        if(!i || (']' != *h))
          return CURLUE_MALFORMED_INPUT;
        zoneid[i] = 0;
        u->zoneid = strdup(zoneid);
        if(!u->zoneid)
          return CURLUE_OUT_OF_MEMORY;
        hostname[len] = ']'; /* insert end bracket */
        hostname[len + 1] = 0; /* terminate the hostname */
      }
      else
        return CURLUE_MALFORMED_INPUT;
      /* hostname is fine */
    }
#ifdef ENABLE_IPV6
    hostname[hlen] = 0; /* end the address there */
    if(1 != Curl_inet_pton(AF_INET6, hostname, dest))
      return CURLUE_MALFORMED_INPUT;
    hostname[hlen] = ']'; /* restore ending bracket */
#endif
  }
  else {
    /* letters from the second string is not ok */
    len = strcspn(hostname, " ");
    if(hlen != len)
      /* hostname with bad content */
      return CURLUE_MALFORMED_INPUT;
  }
  if(!hostname[0])
    return CURLUE_NO_HOST;
  return CURLUE_OK;
}