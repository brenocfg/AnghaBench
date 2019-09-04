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
struct sockaddr {int dummy; } ;

/* Variables and functions */
 unsigned int IPV6_SCOPE_GLOBAL ; 

unsigned int Curl_ipv6_scope(const struct sockaddr *sa)
{
#ifndef ENABLE_IPV6
  (void) sa;
#else
  if(sa->sa_family == AF_INET6) {
    const struct sockaddr_in6 * sa6 = (const struct sockaddr_in6 *)(void *) sa;
    const unsigned char *b = sa6->sin6_addr.s6_addr;
    unsigned short w = (unsigned short) ((b[0] << 8) | b[1]);

    if((b[0] & 0xFE) == 0xFC) /* Handle ULAs */
      return IPV6_SCOPE_UNIQUELOCAL;
    switch(w & 0xFFC0) {
    case 0xFE80:
      return IPV6_SCOPE_LINKLOCAL;
    case 0xFEC0:
      return IPV6_SCOPE_SITELOCAL;
    case 0x0000:
      w = b[1] | b[2] | b[3] | b[4] | b[5] | b[6] | b[7] | b[8] | b[9] |
          b[10] | b[11] | b[12] | b[13] | b[14];
      if(w || b[15] != 0x01)
        break;
      return IPV6_SCOPE_NODELOCAL;
    default:
      break;
    }
  }
#endif

  return IPV6_SCOPE_GLOBAL;
}