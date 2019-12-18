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
struct Curl_easy {int dummy; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_NOT_BUILT_IN ; 
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 scalar_t__ ISALPHA (char) ; 
 scalar_t__ ISXDIGIT (char) ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*,...) ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 long strtol (char*,char**,int) ; 

__attribute__((used)) static CURLcode parse_connect_to_host_port(struct Curl_easy *data,
                                           const char *host,
                                           char **hostname_result,
                                           int *port_result)
{
  char *host_dup;
  char *hostptr;
  char *host_portno;
  char *portptr;
  int port = -1;

#if defined(CURL_DISABLE_VERBOSE_STRINGS)
  (void) data;
#endif

  *hostname_result = NULL;
  *port_result = -1;

  if(!host || !*host)
    return CURLE_OK;

  host_dup = strdup(host);
  if(!host_dup)
    return CURLE_OUT_OF_MEMORY;

  hostptr = host_dup;

  /* start scanning for port number at this point */
  portptr = hostptr;

  /* detect and extract RFC6874-style IPv6-addresses */
  if(*hostptr == '[') {
#ifdef ENABLE_IPV6
    char *ptr = ++hostptr; /* advance beyond the initial bracket */
    while(*ptr && (ISXDIGIT(*ptr) || (*ptr == ':') || (*ptr == '.')))
      ptr++;
    if(*ptr == '%') {
      /* There might be a zone identifier */
      if(strncmp("%25", ptr, 3))
        infof(data, "Please URL encode %% as %%25, see RFC 6874.\n");
      ptr++;
      /* Allow unreserved characters as defined in RFC 3986 */
      while(*ptr && (ISALPHA(*ptr) || ISXDIGIT(*ptr) || (*ptr == '-') ||
                     (*ptr == '.') || (*ptr == '_') || (*ptr == '~')))
        ptr++;
    }
    if(*ptr == ']')
      /* yeps, it ended nicely with a bracket as well */
      *ptr++ = '\0';
    else
      infof(data, "Invalid IPv6 address format\n");
    portptr = ptr;
    /* Note that if this didn't end with a bracket, we still advanced the
     * hostptr first, but I can't see anything wrong with that as no host
     * name nor a numeric can legally start with a bracket.
     */
#else
    failf(data, "Use of IPv6 in *_CONNECT_TO without IPv6 support built-in!");
    free(host_dup);
    return CURLE_NOT_BUILT_IN;
#endif
  }

  /* Get port number off server.com:1080 */
  host_portno = strchr(portptr, ':');
  if(host_portno) {
    char *endp = NULL;
    *host_portno = '\0'; /* cut off number from host name */
    host_portno++;
    if(*host_portno) {
      long portparse = strtol(host_portno, &endp, 10);
      if((endp && *endp) || (portparse < 0) || (portparse > 65535)) {
        infof(data, "No valid port number in connect to host string (%s)\n",
              host_portno);
        hostptr = NULL;
        port = -1;
      }
      else
        port = (int)portparse; /* we know it will fit */
    }
  }

  /* now, clone the cleaned host name */
  if(hostptr) {
    *hostname_result = strdup(hostptr);
    if(!*hostname_result) {
      free(host_dup);
      return CURLE_OUT_OF_MEMORY;
    }
  }

  *port_result = port;

  free(host_dup);
  return CURLE_OK;
}